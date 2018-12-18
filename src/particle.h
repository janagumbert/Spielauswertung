#pragma once

#ifndef PARTICLE_H
#define PARTICLE_H

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"

class theParticle {

public:
	theParticle();
	~theParticle();

	void setup(ofVec2f position);
	void update(float deltaT, ofVec2f attractor);
	void draw();

	float getAgeNorm();

private:
	ofColor color;      //Farbe
	float size;         //Gr��e
	float mass;         //Masse
	bool time;

	ofVec2f velocity;   //Geschwindigkeit
	ofVec2f velocity2;   //Geschwindigkeit
	ofVec2f position;   //Position

	float maxLife;         //Leben
	float age;          // Wie alt darf er werden

	vector<theParticle*> system;
};
#endif 