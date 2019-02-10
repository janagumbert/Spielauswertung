//
//  particleSwitch.hpp
//  ParticleSwitch
//
//  Created by Fritz Lenssen on 07.01.19.
//

#ifndef particleSwitch_hpp
#define particleSwitch_hpp

#pragma once
#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"

#endif /* particleSwitch_hpp */

class particle02
{
public:
    
    particle02();
    ~particle02();
    
    ofVec2f vel;
	ofVec2f velocity2;
    ofVec2f pos;
    ofVec2f force;

	ofColor color;

    float maxLife;
    float age;
    float getAgeNorm();
	float size;
	float mass;
	float shallBeKilled();
	bool pL;
  
    void setup(ofVec2f pos, float maxAge);
    void startTornado();
    void startStage1();
    void updateStage1();
    void updateParticle(double deltaT, ofVec2f attractor, bool cloudAttractorIsSet, bool tornadoIsFinished);
    void draw();
    void keyReleased(int key);
    void keyPressed(int key);
  
private: 

};
