#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofBackground(0);
	width = ofGetWidth();
	height = ofGetHeight();
	cropWidth = height*height / width;

	kinect.open();
	kinect.init(true, true); // color, body
	user = User(kinect.getCoordinateMapper());

	handOpen.load(ofToDataPath("icn_openHand.png"));
	handClose.load(ofToDataPath("icn_closedHand.png"));

	// do menu setup here

	// cut menu
	HorzMenu cutMenu(width*0.5 - cropWidth*0.5, height*0.5, cropWidth, 5);
	VertMenu vCutMenu(width*0.5 + cropWidth*0.5 - 120, 100, cropWidth, 5);
	ofImage btnCut; btnCut.load(ofToDataPath("button_cut.png"));
	for (int i = 0; i < 10; i++) {
		cutMenu.addButton(btnCut);
		vCutMenu.addButton(btnCut);
	}
	hMenus.push_back(cutMenu);
	vMenus.push_back(vCutMenu);

	// category menu
	HorzMenu catMenu(width*0.5 - cropWidth*0.5, height*0.5, cropWidth, 5);
	VertMenu vCatMenu(width*0.5 + cropWidth*0.5 - 120, 100, cropWidth, 5);
	ofImage btnCat; btnCat.load(ofToDataPath("button_category.png"));
	for (int i = 0; i < 10; i++) {
		catMenu.addButton(btnCat);
		vCatMenu.addButton(btnCat);
	}
	hMenus.push_back(catMenu);
	vMenus.push_back(vCatMenu);

	// pattern menu
	HorzMenu patMenu(width*0.5 - cropWidth*0.5, height*0.5, cropWidth, 5);
	VertMenu vPatMenu(width*0.5 + cropWidth*0.5 - 120, 100, cropWidth, 5);
	ofImage btnPat; btnPat.load(ofToDataPath("button_pattern.png"));
	for (int i = 0; i < 10; i++) {
		patMenu.addButton(btnPat);
		vPatMenu.addButton(btnPat);
	}
	hMenus.push_back(patMenu);
	vMenus.push_back(vPatMenu);

}

//--------------------------------------------------------------
void ofApp::update() {

	kinect.update();
	if (!kinect.hasColorStream()) return;

	bNewUser = user.setBody(kinect.getCentralBodyPtr());
	user.update();
	bUser = user.hasBody();

	if (bUser) {
		bool bRelease = false;
		if (!bNewUser) {
			HandState rhState = user.getRightHandState();
			if (!bGrabbing){ // was not grabbing
				if (rhState == HandState_Closed) {
					// closed hand to init new grab
					bGrabbing = true;
				}
			}
			else { // was grabbing
				if (rhState != HandState_Unknown &&
					rhState != HandState_Closed) {
					// must be closed or unknown to continue grab
					// otherwise, release
					bGrabbing = false;
					bRelease = true;
				}
			}
		}
		else { // new user, reset grab
			bGrabbing = false;
		}
		// has user - get right hand pos
		rHandPos = user.getJoint2dPos(JointType_HandRight);

		// do menu interaction
		if (bRelease) {
			menuRelease(rHandPos);
		}
		else if (bGrabbing) {
			menuGrab(rHandPos);
		}
		else { // hover
			menuHover(rHandPos);
			if (hoverTime >= hoverWait) {
				nextMenu();
			}
		}
	}
	else { // no user
		bGrabbing = false;
		resetMenu();
	}

	updateMenu();
}

//--------------------------------------------------------------
void ofApp::draw(){

	vertScreen.begin();
	{
		if (drawUser){
			kinect.drawColor();
			user.draw();
		}

		drawMenu();

		// hand icons
		if (bUser && !bGrabbing) {
			ofVec2f cPos = user.getJoint2dPos(JointType_HandRight);
			ofVec2f oPos(cPos.x - handOpen.getWidth()*0.5, cPos.y - handOpen.getWidth()*0.5);
			if (hoverTime > 0) {
				// draw growing arc
				ofPushStyle();
				// arc bg
				float radius = handOpen.getHeight()*0.55f;
				ofSetColor(0);
				ofSetLineWidth(15);
				ofPolyline timerbg;
				timerbg.arc(cPos, radius, radius, 0, 360, 60);
				timerbg.draw();
				// arc
				ofSetColor(255);
				ofSetLineWidth(10);
				ofPolyline timer;
				float angleEnd = ofMap(hoverTime, 0, hoverWait, 1, 360, true);
				timer.arc(cPos, radius, radius, 0, angleEnd, 60);
				timer.draw();
				ofPopStyle();
			}
			handOpen.draw(oPos);

		}
		else if (bUser && bGrabbing) {
			ofVec2f cPos = user.getJoint2dPos(JointType_HandRight);
			ofVec2f oPos(cPos.x - handClose.getWidth()*0.5, cPos.y - handClose.getWidth()*0.5);
			handClose.draw(oPos);
		}
	}
	vertScreen.end();

}

//--------------------------------------------------------------

void ofApp::menuHover(ofVec2f pos) {
	if (cMenu >= 0 && cMenu < 3) {
		if (bHorzMenu) { 
			hMenus[cMenu].hover(pos);
			hoverTime = hMenus[cMenu].getHoverTime();
		}
		else {
			vMenus[cMenu].hover(pos);
			hoverTime = vMenus[cMenu].getHoverTime();
		}
	}
	else if (cMenu == -1) {
		lineUpMenu.hover(pos);
		hoverTime = lineUpMenu.getHoverTime();
	}
	else {
		wearMenu.hover(pos);
		hoverTime = wearMenu.getHoverTime();
	}
}

void ofApp::menuGrab(ofVec2f pos) {
	if (cMenu >= 0 && cMenu < 3) {
		if (bHorzMenu) {
			hMenus[cMenu].grab(pos);
		}
		else {
			vMenus[cMenu].grab(pos);
		}
	}
	else if (cMenu == -1) {
		lineUpMenu.grab(pos);
	}
	else {
		wearMenu.grab(pos);
	}
}

void ofApp::menuRelease(ofVec2f pos) {
	if (cMenu >= 0 && cMenu < 3) {
		if (bHorzMenu) {
			hMenus[cMenu].release(pos);
		}
		else {
			vMenus[cMenu].release(pos);
		}
	}
	else if (cMenu == -1) {
		lineUpMenu.release(pos);
	}
	else {
		wearMenu.release(pos);
	}
}

void ofApp::prevMenu() {
	if (cMenu >= 0 && cMenu < 3) {
		hMenus[cMenu].resetState();
		vMenus[cMenu].resetState();
	}
	if (cMenu != -1) cMenu--;
}

void ofApp::nextMenu() {
	if (cMenu >= 0 && cMenu < 3) {
		hMenus[cMenu].resetState();
		vMenus[cMenu].resetState();
	}
	if (cMenu != 3) cMenu++;
}

void ofApp::resetMenu() {
	if (cMenu >= 0 && cMenu < 3) {
		hMenus[cMenu].resetState();
		vMenus[cMenu].resetState();
	}
	else if (cMenu == -1) {
		lineUpMenu.resetState();
	}
	else {
		wearMenu.resetState();
	}
}

void ofApp::restartMenus() {
	resetMenu();
	cMenu = -1;
}

void ofApp::updateMenu() {
	if (cMenu >= 0 && cMenu < 3) {
		if (bHorzMenu) {
			hMenus[cMenu].update();
		}
		else {
			vMenus[cMenu].update();
		}
	}
	else if (cMenu == -1) {
		lineUpMenu.update();
	}
	else {
		wearMenu.update();
	}
}

void ofApp::drawMenu() {
	if (cMenu >= 0 && cMenu < 3) {
		if (bHorzMenu) {
			hMenus[cMenu].drawScreenOverlay(cropOrig,cropWidth,height);
			hMenus[cMenu].drawMenu();
		}
		else {
			vMenus[cMenu].drawScreenOverlay(cropOrig, cropWidth, height);
			vMenus[cMenu].drawMenu();
		}
	}
	else if (cMenu == -1) {
		lineUpMenu.drawScreenOverlay(cropOrig, cropWidth, height);
		lineUpMenu.drawMenu();
	}
	else {
		wearMenu.drawScreenOverlay(cropOrig, cropWidth, height);
		wearMenu.drawMenu();
	}
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'v' || key == 'V') {
		vertScreen.nextScreenMode();
	}
	else if (key == 'u' || key == 'U') {
		drawUser = !drawUser;
	}
	else if (key == 'm' || key == 'M') {
		bHorzMenu = !bHorzMenu;
	}
	else if (key == OF_KEY_LEFT) {
		// page menu back
	}
	else if (key == OF_KEY_RIGHT) {
		// page menu forward
	}
	else if (key == 'n' || key == 'N') {
		nextMenu();
	}
	else if (key == 'p' || key == 'P') {
		prevMenu();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	menuHover(ofVec2f(x, y));
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	menuGrab(ofVec2f(x, y));
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	menuGrab(ofVec2f(x, y));
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	menuRelease(ofVec2f(x, y));
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
