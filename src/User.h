#pragma once
#include "ofMain.h"
#include "ofxKinectForWindows2.h"

class User {
protected:
	struct HandStates {
		HandState left = HandState_Unknown;
		HandState right = HandState_Unknown;
	};
	struct Joint2fData {
		ofVec2f pos = ofVec2f(0, 0);
		TrackingState state = TrackingState_NotTracked;
	};

	typedef map<JointType, Joint2fData> JointMap2f;


public:
	typedef const ofxKFW2::Data::Body kBody;

	User(ICoordinateMapper* coordinateMapperPtr = nullptr)
		: _coordMapperPtr(coordinateMapperPtr) {
	}

	void setCoordinateMapper(ICoordinateMapper* coordinateMapperPtr)
	{
		_coordMapperPtr = coordinateMapperPtr;
	}

	bool setBody(kBody* body); // returns false if same body
	bool update(); // false is _bodyPtr is nullptr

	bool jointExists(JointType type, bool prev = false);
	ofVec2f getJoint2dPos(JointType type, bool prev=false);
	TrackingState getTrackingState(JointType type, bool prev=false);
	HandState getLeftHandState(bool prev = false);
	HandState getRightHandState(bool prev = false);
	bool isRightHandUp();
	bool isLeftHandUp();
	bool hasBody() { return (_bodyPtr != nullptr); }
	bool hasCoordinateMapper() { return (_coordMapperPtr != nullptr); }

	void draw(ofVec2f pos, float width, float height);
	void draw() { draw(ofVec2f(0, 0), 1920, 1080); }
	void drawJoints2d(ofVec2f pos, float width, float height);
	void drawJoints2d() { drawJoints2d(ofVec2f(0, 0), 1920, 1080); }
	void drawHandStates(ofVec2f pos, float width, float height);
	void drawHandStates() { drawHandStates(ofVec2f(0, 0), 1920, 1080); }
	void drawHandState(JointType hand, ofVec2f pos, float width, float height);
	void drawHandState(JointType hand) { drawHandState(hand, ofVec2f(0, 0), 1920, 1080); }

	void clear();

protected:

	kBody* _bodyPtr = nullptr;
	ICoordinateMapper* _coordMapperPtr;

	JointMap2f _joints2d; // joints positions in 2d colorcam space
	JointMap2f _pJoints2d; // previous frame
	HandStates _handStates; // left, right
	HandStates _pHandStates; // previous frame

};
