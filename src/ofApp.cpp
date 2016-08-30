#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
	width = ofGetWidth();
	height = ofGetHeight();

	kinect.open();
	kinect.init(true,true); // color, body
	user = User(kinect.getCoordinateMapper());

	// do menu setup here
	
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

	startVertScreen();

	kinect.drawColor();
	user.draw();

	endVertScreen(screenMode);

}

void ofApp::startVertScreen() {
	if (screen.getWidth() != width || screen.getHeight() != height) {
		screen.allocate(width, height, GL_RGBA);
	}
	screen.begin();
	ofClear(ofGetBackgroundColor());
}

void ofApp::endVertScreen(VertScreenMode vScreenMode) {

	screen.end();
	// draw fbo at appropriate settings

	if (vScreenMode == VertScreenLeft || vScreenMode == VertScreenRight) {
		ofPushMatrix();
		ofRotateZ(-90);
		float zoom = width / height; // so new height == old width
		ofScale(zoom, zoom);
		float trX = -width*0.5f - (height / zoom)*0.5f;
		ofTranslate(trX, 0);

		if (vScreenMode == VertScreenRight) {
			ofTranslate(width*0.5, height*0.5);
			ofRotate(180);
			ofTranslate(-width*0.5, -height*0.5);
		}

		screen.draw(0, 0, width, height);
		ofPopMatrix();
	}
	else if (vScreenMode == SimVertScreen) {
		ofTexture& tex = screen.getTexture();
		float sw = height * height / width;
		float sx = width*0.5f - sw*0.5f;
		tex.drawSubsection(sx, 0, sw, height, sx, 0, sw, height);
	}
	else {
		screen.draw(0, 0, width, height);
	}

}

void ofApp::nextScreenMode() {
	switch (screenMode) {
		case VertScreenLeft: screenMode = VertScreenRight; break;
		case VertScreenRight: screenMode = SimVertScreen; break;
		case SimVertScreen: screenMode = HorzScreen; break;
		case HorzScreen: screenMode = VertScreenLeft; break;
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'v' || key == 'V') {
		nextScreenMode();
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
