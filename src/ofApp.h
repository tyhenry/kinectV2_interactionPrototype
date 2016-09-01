#pragma once

#include "ofMain.h"
#include "ofxKinectForWindows2.h"
#include "ofxGui.h"
#include "Kinect.h"
#include "User.h"
#include "VertScreen.h"
#include "HorzMenu.h"
#include "Button.h"


class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();


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
	//Menu menu;

	VertScreen vertScreen;
	float width = 1920;
	float height = 1080;

	// menu states
	HorzMenu cutMenu; // 0
	HorzMenu catMenu; // 1
	HorzMenu patMenu; // 2
	// 3 == wear

	ofImage handOpen;
	ofImage handClose;
		
};


