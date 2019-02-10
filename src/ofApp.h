#pragma once

#include "ofMain.h"
#include "particleSwitch.h"

#include "ofxOpenCv.h"
#include "ofTrueTypeFont.h"
#include "ofxCv.h"

//#define MAXNUMPARTICELS 37126


class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void startTornado();
	void updateTornado();

	vector <ofVec2f> pixelInVector(ofImage a);
	

private:
	vector<ofVec2f>attractors;
	vector<particle02*> system;
	ofVec2f force;

	ofImage fileImage1;
	ofImage fileImage2;
	ofImage fileImage3;
	
	int maxParticle;
	int picPix;
	bool symbolAttractorIsSet;
	bool cloudAttractorIsSet;
	bool tornadoIsFinished;
	bool tornadoStarted;
	bool drawAllPixel;

	//------------------------------------------
	float birthCnt;
	float maxLife;
	float parAmount;
	float height;
	double time;
	double tornadoStartTime;
	int status;

};