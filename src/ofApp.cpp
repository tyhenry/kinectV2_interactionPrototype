#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
	width = ofGetWidth();
	height = ofGetHeight();

	kinect.open();
	kinect.init(true,true); // color, body
	user = User(kinect.getCoordinateMapper());

	handOpen.load(ofToDataPath("icn_openHand.png"));
	handClose.load(ofToDataPath("icn_closedHand.png"));

	// do menu setup here
	// cutMenu
	cutMenu = HorzMenu(width*0.5-height*0.5, height*0.6, height, height/5);
	ofImage btnCut; btnCut.load(ofToDataPath("button_cut.png"));
	for (int i=0; i<5; i++) cutMenu.addButton(btnCut);

	catMenu = HorzMenu(width*0.5 - height*0.5, height*0.6, height, height / 5);
	ofImage btnCat; btnCat.load(ofToDataPath("button_category.png"));
	for (int i = 0; i<5; i++) cutMenu.addButton(btnCat);

	patMenu = HorzMenu(width*0.5 - height*0.5, height*0.6, height, height / 5);
	ofImage btnPat; btnPat.load(ofToDataPath("button_pattern.png"));
	for (int i = 0; i<5; i++) cutMenu.addButton(btnPat);
}

//--------------------------------------------------------------
void ofApp::update(){

	kinect.update();
	if (!kinect.hasColorStream()) return;

	user.setBody(kinect.getCentralBodyPtr());
	user.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

	vertScreen.begin();

	kinect.drawColor();
	user.draw();
	cutMenu.drawMenu();
	if (user.getRightHandState() == HandState_Open) {
		ofVec2f cPos = user.getJoint2dPos(JointType_HandRight);
		ofVec2f oPos(cPos.x - handOpen.getWidth()*0.5, cPos.y - handOpen.getWidth()*0.5);
		handOpen.draw(oPos);
	}
	else if (user.getRightHandState() == HandState_Closed) {
		ofVec2f cPos = user.getJoint2dPos(JointType_HandRight);
		ofVec2f oPos(cPos.x - handClose.getWidth()*0.5, cPos.y - handClose.getWidth()*0.5);
		handClose.draw(oPos);
	}

	vertScreen.end();

}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'v' || key == 'V') {
		vertScreen.nextScreenMode();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
