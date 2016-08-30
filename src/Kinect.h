#pragma once
#include "ofMain.h"
#include "ofxKinectForWindows2.h"

class Kinect : public ofxKFW2::Device {

public:
	typedef const ofxKFW2::Data::Body kBody;

	Kinect() {};
	void init(bool bColor=true, bool bBody=true,
		 bool bDepth=false, bool bBodyIdx= false, bool bIR=false, bool bIRLong = false);

	kBody* getCentralBodyPtr(float bodyQualityThreshold=0.0);
	int getCentralBodyIndex(float bodyQualityThreshold=0.0); // returns -1 if no bodies

	kBody* getBodyPtrByIndex(int bodyIndex);
	int getNumTrackedBodies();

	ICoordinateMapper* getCoordinateMapper() { return _coordinateMapper; }
	bool hasColorStream() { return getColorPixels().size() > 0; }
	ofPixels& getColorPixels() { return getColorSource()->getPixels(); }
	ofTexture& getColorTexture() { return getColorSource()->getTexture(); }
	float getColorWidth() { return getColorSource()->getWidth(); }
	float getColorHeight() { return getColorSource()->getHeight(); }

	void drawColor(float x, float y, float w, float h);
	void drawColor() { drawColor(0, 0, 1920, 1080); }
	void drawColorSubsection(float x, float y, float w, float h,
							float sx, float sy, float sw, float sh);


protected:

	ICoordinateMapper* _coordinateMapper;
};