#include "Kinect.h"

void Kinect::init(bool bColor, bool bBody, bool bDepth, bool bBodyIdx, bool bIR, bool bIRLong) {

	if (bColor) initColorSource();
	if (bBody) initBodySource();
	if (bDepth) initDepthSource();
	if (bBodyIdx) initBodyIndexSource();
	if (bIR) initInfraredSource();
	if (bIRLong) initLongExposureInfraredSource();

	if (getSensor()->get_CoordinateMapper(&_coordinateMapper) < 0) {
		ofLogError("Kinect") << "couldn't aquire coordinate mapper!";
	}
	else {
		ofLogVerbose("Kinect") << "aquired coordinate mapper";
	}
	setUseTextures(true); // not sure if necessary
}

Kinect::kBody* Kinect::getBodyPtrByIndex(int bodyIndex) {

	auto& bodies = getBodySource()->getBodies();
	if (bodyIndex > 0 && bodyIndex < bodies.size()) {
		return &(bodies[bodyIndex]);
	}
	return nullptr;
}

int Kinect::getCentralBodyIndex(float bodyQualityThreshold) {

	auto & bodies = getBodySource()->getBodies();

	int closestIdx = -1;
	float closestDist = 99999.f;
	for (int i = 0; i < bodies.size(); i++) {
		if (!bodies[i].tracked) continue; // skip untracked body
		float dist = abs(bodies[i].joints.at(JointType_SpineBase).getPosition().x);
		if (dist < closestDist) {
			closestIdx = i;
			closestDist = dist;
		}
	}
	return closestIdx;
}

Kinect::kBody* Kinect::getCentralBodyPtr(float threshold) {
	int bodyIdx = getCentralBodyIndex();
	if (bodyIdx < 0) return nullptr;	
	return getBodyPtrByIndex(bodyIdx);
}


int Kinect::getNumTrackedBodies() {
	int n = 0;
	for (auto& body : getBodySource()->getBodies()) {
		if (body.tracked) n++;
	}
	return n;
}

void Kinect::drawColor(float x, float y, float w, float h) {
	getColorTexture().draw(x, y, w, h);
}

void Kinect::drawColorSubsection(float x, float y, float w, float h,
	float sx, float sy, float sw, float sh) {

	getColorTexture().drawSubsection(x, y, w, h, sx, sy, sw, sh);
}
