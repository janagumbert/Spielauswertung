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
    
    float maxLife;
    float age;
    float getAgeNorm();
//    int status;
    bool pL;
    
    ofColor color;
    float size;
    float mass;
    void setup(ofVec2f pos, float maxAge);
    void startTornado();
    void startStage1();
    void updateStage1();
    void updateParticle(double deltaT, ofVec2f attractor, bool deleteAttractor, bool noAttractor, bool tornadoFinished);
    void draw();
    float shallBeKilled();
    void keyReleased(int key);
    void keyPressed(int key);
    
    
    
private:
    

};
