#pragma once

#include "ofMain.h"
#include "ofxKinectForWindows2.h"
#include "ofxGui.h"
#include "Kinect.h"
#include "User.h"
#include "VertScreen.h"
#include "HorzMenu.h"
#include "VertMenu.h"
#include "Button.h"


class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void menuHover(ofVec2f pos);
	void menuGrab(ofVec2f pos);
	void menuRelease(ofVec2f pos);
	void prevMenu();
	void nextMenu();
	void resetMenu();
	void restartMenus();
	void updateMenu();
	void drawMenu();

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
	ofVec2f cropOrig;
	float cropWidth;

	// menus
	int cMenu = -1;
	bool bHorzMenu = true;
	vector<HorzMenu> hMenus;
	vector<VertMenu> vMenus;
	HorzMenu lineUpMenu;
	HorzMenu wearMenu;
	// -1 - line up body
	// 0 - cut
	// 1 - category
	// 2 - pattern
	// 3 - wear

	ofImage handOpen;
	ofImage handClose;

	bool bUser = false;
	bool bGrabbing = false;
	bool bNewUser = true;
	ofVec2f rHandPos;
	float hoverTime = 0;
	float hoverWait = 3; // sec until select
	ofVec2f headAlign;

	bool drawUser = true;	
};


