#include "ofApp.h"
#include "ofxOpenCv.h"
#include "ofTrueTypeFont.h"


//--------------------------------------------------------------
void ofApp::setup() {

	ofSetBackgroundColor(0, 0, 0);
	ofSetFrameRate(60);
	maxParticle = 50;
	fileImage.loadImage("Ohm.png");

	attractors = pixelInVector(fileImage);


	birthCnt = 0;
	sterben = false;
	tornado = false;
	tornadoFinished = false;
	grenze.set(0, ofGetHeight() - 240);
	grenze2.set(0, ofGetHeight() - 640);
	life = true;
	parAmount = 3;
	tornadoStartTime = -1000;
	time = 0;
	status = -1;
}


//--------------------------------------------------------------
void ofApp::update() {

	double deltaT = ofGetLastFrameTime();

	//----------------------------------------

	time += deltaT;

	//birthCnt += ofGetLastFrameTime();

	if (birthCnt > 0.001 && status == -1) {
		for (int i = 0; i < parAmount; i++) {
			system.push_back(new particle02);
			system.back()->setup(ofVec2f(ofRandom(0, ofGetWidth()), 0), 20);
			past1 = false;
		}
		birthCnt = 0;
	}

	for (int p = 0; p < system.size(); p++) {
		particle02* partikel = system.at(p);

		partikel->updateParticle(deltaT, ofVec2f(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())), deleteAttractor, noAttractor, tornadoFinished);

		if (system.at(p)->shallBeKilled()) {
			delete system.at(p);
			system.erase(system.begin() + p);
			p--;
		}
	}
	updateTornado();
	
	//---------------------------------------
	

	if (system.size() < picPix / 7 + 100) {

		for (int i = 0; i < maxParticle; i++) {    //erzeugt pro frame 50 neue partikel an zufälliger Stelle
			system.push_back(new particle02);

			int y = ofRandomHeight();
			int x = ofRandomWidth();

			system.back()->setup(ofVec2f(x, y), 20);  //maxAge auf 20
		}

	}
	

	if (tornadoFinished == true) {
		for (int p = 0; p < system.size();) {
			if (p * 7 < attractors.size()) {
				if (drawAttractor == false) {
					system.at(p)->updateParticle(deltaT, ofVec2f(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())), deleteAttractor, noAttractor, tornadoFinished); //Partikel werden an beliebige stelle gezogen				
				}
				else
				{
					system.at(p)->updateParticle(deltaT, attractors[p * 7], deleteAttractor, noAttractor, tornadoFinished);//wie genau wird img gezeichnet(jedes 10. pixel)
				}
			}
			else {
				system.at(p)->updateParticle(deltaT, ofVec2f(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())), deleteAttractor, noAttractor, tornadoFinished); //Partikel werden an beliebige stelle gezogen
			}
			p++;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (int i = 0; i < system.size(); i++) {
		system.at(i)->draw();
		//i = i + 2;
	}
}

vector<ofVec2f> ofApp::pixelInVector(ofImage a) {
	int picWidth = a.getWidth();
	int picHeight = a.getHeight();
	ofPixels pix;
	pix = a.getPixels();
	vector<ofVec2f> pxPos;
	for (int i = 3; i <= pix.size(); i += 4) {
		if (pix[i] > 0) {
			int width = pix.getWidth();

			int y = i / 4 / width;

			int x = i / 4 % width;

			ofVec2f vec;
			vec.set(x + ((ofGetWidth() / 2) - picWidth / 2), y + ((ofGetHeight() / 2) - picHeight / 2));

			pxPos.push_back(vec);

			picPix++;
		}
	}
	return pxPos;
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {			//alle Partikel sterben nach ablaufen des maxAge und wenn man eine Taste loslässt.

	//--------------------------------

	switch (key) {
	case ' ':
		for (int p = 0; p < system.size();) {	//durchgehen der Partikel
			if (system.at(p)->getAgeNorm() >= 1) {	//schauen ob maxAge erreicht
				delete system.at(p);
				system.erase(system.begin() + p);	//löschen der Partikel
			}
			p++;
		}
		maxParticle = 0;	// damit keine neuen Partikel durch die update-Methode ersellt werden.
		break;
	case 'a':
		startTornado();
		tornadoFinished = false;
		break;
	case 'd':
		deleteAttractor = true;
		noAttractor = false;
		tornadoFinished = true;
		break;

	case 'f':
		noAttractor = true;
		deleteAttractor = false;
		tornadoFinished = true;
		break;
	case 's':
		drawAttractor = true;		// setze des Booleans um den Bild-Attraktor zu setzen
		noAttractor = false;
		deleteAttractor = false;
		tornadoFinished = true;
		break;
	}
}

//--------------------------------------------------------------
void ofApp::startTornado() {
	status = 0;
	tornadoStartTime = time;
	for (int p = 0; p < system.size(); p++) {
		particle02* partikel = system.at(p);
		partikel->startTornado();
	}

}

//--------------------------------------------------------------
void ofApp::updateTornado() {
	switch (status) {
	case 0:
		if ((time - tornadoStartTime) > 1.9) {
			status = 1;
			for (int p = 0; p < system.size(); p++) {
				particle02* partikel = system.at(p);
				partikel->startStage1();
			}
		}
		break;
	case 1:
		if ((time - tornadoStartTime) > 15) {
			status = -1;
		}
		for (int p = 0; p < system.size(); p++) {
			particle02* partikel = system.at(p);
			partikel->updateStage1();
		}
		break;
		//        case 2:
		//            if ((pos.y ))
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}