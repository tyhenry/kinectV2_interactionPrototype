#pragma once

#include "ofMain.h"
#include "ofxKinectForWindows2.h"
#include "ofxGui.h"
#include "Kinect.h"
#include "User.h"
#include "Menu.h"

enum VertScreenMode {
	VertScreenLeft,
	VertScreenRight,
	SimVertScreen,
	HorzScreen
};

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	void startVertScreen();
	void endVertScreen(VertScreenMode vScreenMode);

	void nextScreenMode();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	Kinect kinect;
	User user;
	Menu menu;

	VertScreenMode screenMode = SimVertScreen;
	ofFbo screen;
	float width = 1920;
	float height = 1080;
		
};
