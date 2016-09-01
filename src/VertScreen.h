#pragma once
#include "ofMain.h"

// note:
// this code could be refactored for choice of zoom 
// or draw at native resolution
 
class VertScreen {
public:
	enum VertScreenMode {
		VertScreenLeft,
		VertScreenRight,
		SimVertScreen,
		HorzScreen
	};
protected:
	ofFbo _screen;
	VertScreenMode _mode = SimVertScreen;
	bool _begun = false;
	float w, h;
public:

	VertScreen() {}
	void begin();
	void end(VertScreenMode mode);
	void end() { end(_mode); }
	VertScreenMode& getScreenMode() { return _mode; }
	VertScreenMode& nextScreenMode();
	VertScreenMode& setScreenMode(VertScreenMode mode) {
		_mode = mode;
	}
};