#include "VertScreen.h"

void VertScreen::begin() {

	w = ofGetWidth();
	h = ofGetHeight();
	if (_screen.getWidth() != w || _screen.getHeight() != h) {
		_screen.allocate(w, h, GL_RGBA);
	}
	_screen.begin();
	ofClear(ofGetBackgroundColor());
	_begun = true;
}

void VertScreen::end(VertScreenMode mode) {
	if (!_begun) return;

	_screen.end();
	// draw fbo at appropriate settings

	if (mode == VertScreenLeft || mode == VertScreenRight) {
		ofPushMatrix();
		ofRotateZ(-90);
		float zoom = w / h; // so new height == old width
		ofScale(zoom, zoom);
		float trX = -w*0.5f - (h / zoom)*0.5f;
		ofTranslate(trX, 0);

		if (mode == VertScreenRight) {
			ofTranslate(w*0.5, h*0.5);
			ofRotate(180);
			ofTranslate(-w*0.5, -h*0.5);
		}

		_screen.draw(0, 0, w, h);
		ofPopMatrix();
	}
	else if (mode == SimVertScreen) {
		ofTexture& tex = _screen.getTexture();
		float sw = h * h / w;
		float sx = w*0.5f - sw*0.5f;
		tex.drawSubsection(sx, 0, sw, h, sx, 0, sw, h);
	}
	else {
		_screen.draw(0, 0, w, h);
	}
	_begun = false;
}

VertScreen::VertScreenMode& VertScreen::nextScreenMode() {
	switch (_mode) {
	case VertScreenLeft: _mode = VertScreenRight; break;
	case VertScreenRight: _mode = SimVertScreen; break;
	case SimVertScreen: _mode = HorzScreen; break;
	case HorzScreen: _mode = VertScreenLeft; break;
	}
	return _mode;
}