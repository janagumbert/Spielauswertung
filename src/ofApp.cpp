#include "ofApp.h"
#include "ofxOpenCv.h"
#include "ofTrueTypeFont.h"


//--------------------------------------------------------------
void ofApp::setup() {

	ofSetBackgroundColor(0, 0, 0);
	ofSetFrameRate(60);
	birthCount = 0;
	maxParticle = 50;
	fileImage.loadImage("FINAL.png");

	attractors = pixelInVector(fileImage);
}


//--------------------------------------------------------------
void ofApp::update() {

	double deltaT = ofGetLastFrameTime();
	
	if (system.size() < picPix/7 - 120) {

		for (int i = 0; i < maxParticle; i++) {    //erzeugt pro frame 50 neue partikel an zufälliger Stelle
			system.push_back(new theParticle);

			int y = ofRandomHeight();
			int x = ofRandomWidth();

			system.back()->setup(ofVec2f(x, y), 20);  //maxAge auf 20 
		}

	}

	for (int p = 0; p < system.size();) {
		if (p * 7 < attractors.size()) {
			
			if (time == false) {
				system.at(p)->update(deltaT, ofVec2f(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()))); //Partikel werden an beliebige stelle gezogen				
			}
			else
			{
				system.at(p)->update(deltaT, attractors[p * 7]);//wie genau wird img gezeichnet(jedes 10. pixel)
			}
		}
		else {
			system.at(p)->update(deltaT, ofVec2f(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()))); //Partikel werden an beliebige stelle gezogen
		}
		p++;
	}


}

//--------------------------------------------------------------
void ofApp::draw() {

	for (int i = 0; i < system.size(); i++) {
		system.at(i)->draw();
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
	for (int p = 0; p < system.size();) {	//durchgehen der Partikel
		if (system.at(p)->getAgeNorm() >= 1) {	//schauen ob maxAge erreicht
			delete system.at(p);	
			system.erase(system.begin() + p);	//löschen der Partikel
		}
		p++;
	}
	maxParticle =  0;			// damit keine neuen Partikel durch die update-Methode ersellt werden.
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