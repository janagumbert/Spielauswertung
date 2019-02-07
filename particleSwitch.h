#pragma once

#ifndef PARTICLESWITCH_H
#define PARTICLESWITCH_H

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"

class particle02 {

public:

	particle02();
	~particle02();

	ofVec2f vel;
	ofVec2f pos;
	ofVec2f force;

	float maxLife;
	float age;
	float getAgeNorm();
	//    int status;
	bool pL;

	ofColor color;
	float size;
	float mass;
	void setup(ofVec2f pos);
	void startTornado();
	void startStage1();
	void updateStage1();
	void updateParticle(double deltaT);
	void draw();
	float shallBeKilled();
	void keyReleased(int key);
	void keyPressed(int key);

private:

};
#endif
