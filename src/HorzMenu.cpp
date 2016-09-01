#include "HorzMenu.h"

int HorzMenu::addButton(ofImage img) {
	int idx = _buttons.size();
	float btnW = (float)_w / (float)_nBtnsDisplay;
	float btnH = btnW; // square tiles
	ofVec2f cPos(_x+btnW*idx+btnW*0.5, _y+btnH*0.5);
	_buttons.push_back(Button(idx,img,cPos,btnW,btnH));
	
	// update carousel
	carousel.length = _buttons.size()*btnW;
	carousel.pagingSize = btnW;

	return idx;
}

int HorzMenu::addStaticButton(ofImage img, ofVec2f pos, float w, float h) {
	int idx = _buttons.size();
	ofVec2f cPos(pos.x + w*0.5, pos.y + h*0.5);
	_buttons.push_back(Button(idx, img, cPos, w, h, true));
	return idx;
}

int HorzMenu::hover(ofVec2f pos) {
	int idx = hitTest(pos);
	if (idx >= 0) {
		// new hover
		if (_hoverIdx != idx) {
			_hoverIdx = idx;
			_hoverStartTime = ofGetElapsedTimef();
		}
	}
	// no hover
	else {
		_hoverIdx = -1;
		_hoverStartTime = 0;
	}
	// set all button hover states
	for (auto& btn : _buttons) {
		if (btn.getIndex() == _hoverIdx) btn.hover();
		else btn.noHover();
	}
	return idx;
}

int HorzMenu::grab(ofVec2f pos) {
	int idx = hitTest(pos);
	// new
	if (_grabIdx == -1) {
		// grab
		if (idx >= 0) {
			// grabbed a button
			_grabIdx = idx;
			_grabPos = pos;
			_grabStartTime = ofGetElapsedTimef();
			if (!_buttons[idx].isStatic()) {
				carousel.grab(-_grabPos.x);
			}
		}
		// no grab
		else {
			_grabIdx = -1;
			_grabPos = ofVec2f(0, 0);
			_grabStartTime = 0;
			//carousel.drop();
		}
	}
	// or drag
	else {
		_grabPos = pos;
		if (!_buttons[_grabIdx].isStatic()) {
			carousel.drag(-_grabPos.x);
		}
	}
	return idx;
}

int HorzMenu::release(ofVec2f pos) {
	_grabStartTime = 0;
	if (_grabIdx != -1 && !_buttons[_grabIdx].isStatic()) {
		carousel.drop();
	}
	int idx = _grabIdx;
	_grabIdx = -1;
	_grabPos = ofVec2f(0, 0);
	return idx;
}

float HorzMenu::getHoverTime() {
	if (_hoverIdx >= 0 && _hoverStartTime != 0) {
		return (ofGetElapsedTimef() - _hoverStartTime);
	}
	return 0;
}

float HorzMenu::getGrabTime() {
	if (_grabIdx >= 0 && _grabStartTime != 0) {
		return (ofGetElapsedTimef() - _grabStartTime);
	}
	return 0;
}

int HorzMenu::hitTest(ofVec2f pos) {
	for (auto& btn : _buttons) {
		if (btn.getBounds().inside(pos)) {
			return btn.getIndex();
		}
	}
	return -1;
}

void HorzMenu::update() {
	carousel.update();
	// update button positions
	int nBtns = _buttons.size();
	float btnW = _w / _nBtnsDisplay;
	for (int i = 0; i < nBtns; i++) {
		if (!_buttons[i].isStatic()) {
			float x = carousel.positionForTile(i, nBtns, btnW);
			_buttons[i].setLeft(_x + x);
		}
	}
}

void HorzMenu::drawScreenOverlay(ofVec2f pos, float w, float h) {
	_overlay.draw(pos, w, h);
}

void HorzMenu::drawMenu() {
	ofPushStyle();
	for (int i = 0; i < _buttons.size(); i++) {
		
		if (_grabIdx == i) // grabbed button
			ofSetColor(255, 220, 220);
		else if (_hoverIdx == i) // hover
			ofSetColor(220, 255, 220);
		_buttons[i].draw();
		ofSetColor(255);
	}
	ofPopStyle();
}