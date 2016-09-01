#pragma once
#include "ofMain.h"
#include "ofxCarousel.h"
#include "Button.h"

class HorzMenu {

public:
	HorzMenu() {}
	// display size
	HorzMenu(float x, float y, float displayWidth, int numButtonsDisplay)
		: _x(x), _y(y), _w(displayWidth), _nBtnsDisplay(numButtonsDisplay)
	{}

	//void setPosition(float x, float y) {
	//	_x = x; _y = y;
	//}
	//void setDisplayWidth(float w) { _w = w; }
	//void setNumButtonsDisplay(int numButtons) {
	//	_nBtnsDisplay = numButtons;
	//}

	// add menu item
	int addButton(ofImage img); // adds from left to right
	void setScreenOverlay(ofImage overlay) { 
		_overlay = overlay; _bOverlay = true;
	}
	int addStaticButton(ofImage img, ofVec2f pos, float w, float h);

	int hover(ofVec2f pos); // returns index of button (-1 if none)
	int grab(ofVec2f pos);
	int release(ofVec2f pos);
	void resetState() {
		_hoverIdx = -1; _grabIdx = -1;
		_hoverStartTime = 0; _grabStartTime = 0;
	}

	float getHoverTime();
	float getGrabTime();
	int getHoverIdx() { return _hoverIdx; }
	int getGrabIdx() { return _grabIdx; }

	void update();

	void drawScreenOverlay(ofVec2f pos, float w, float h);
	void drawMenu();

	int hitTest(ofVec2f pos);

protected:
	ofxCarousel carousel;
	float _x, _y, _w;
	int _nBtnsDisplay;
	ofImage _overlay; bool _bOverlay = false;
	vector<Button> _buttons;
	int _hoverIdx = -1, _grabIdx = -1;
	float _hoverStartTime = 0, _grabStartTime = 0;
	ofVec2f _grabPos;
};