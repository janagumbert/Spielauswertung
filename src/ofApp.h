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
	int maxParticle;

	ofImage fileImage1;
	ofImage fileImage2;
	ofImage fileImage3;
	
	int picPix;
	bool drawAttractor;
	bool deleteAttractor;
	bool noAttractor;
	bool tornadoFinished;
	bool tornadoStarted;


	//------------------------------------------
	vector<particle02*> system;
	ofVec2f grenze;
	ofVec2f grenze2;
	ofVec2f force;

	float birthCnt;
	float maxLife;
	float parAmount;
	float sine;
	ofParameter<float> sinParam;

	double time;
	double tornadoStartTime;
	int stat2;
	int status;
	bool past1;
	bool life;
	bool sterben;
	bool bounce;
	bool tornado;
	float height;
	float distance;
};