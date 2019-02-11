#include "ofApp.h"
#include "ofxOpenCv.h"
#include "ofTrueTypeFont.h"


//--------------------------------------------------------------
void ofApp::setup() {
	ofSetBackgroundColor(0, 0, 0);
	ofSetFrameRate(60);
	maxParticle = 50;
	birthCnt = 0;
	parAmount = 10;
	tornadoStartTime = -1000;
	time = 0;
	status = -1;

	fileImage1.loadImage("Ohm.png");
	fileImage2.loadImage("FINAL_Logo.png");
	fileImage3.loadImage("Danke_4070_2.png");
}


//--------------------------------------------------------------
void ofApp::update() {

//	std::cout << picPix << endl;
	double deltaT = ofGetLastFrameTime();
	time += deltaT;

	//----------------------------------------------------------//ertsellen bzw. löschen von Partikeln
	if ((birthCnt >= 0) && (status == -1) && (tornadoIsFinished == false)) {		//erstellen von Partiklen für Tornado
		for (int i = 0; i < parAmount; i++) {
			system.push_back(new particle02);
			system.back()->setup(ofVec2f(ofRandom(0, ofGetWidth()), 0), 20);
		}
		birthCnt = 0;
	}
	else if ((tornadoIsFinished == true) && (system.size() < picPix / 7)) {			//erstellen von Partiklen für Symbole
		int newPix = (picPix / 7) - system.size();
		for (int i = 1; i <= newPix; i++) {											// Durchgehen ab Partikel i = 1 da es kein Pixel 0 gibt
			system.push_back(new particle02);

			int y = ofRandomHeight();
			int x = ofRandomWidth();

			system.back()->setup(ofVec2f(x, y), 20);
		}
	}
	else if ((tornadoIsFinished == true) && (system.size() > picPix / 7)) {			//Löschen von Überschüssigen Partikeln für Symbole
		int newPix = system.size() - (picPix / 7);
		for (int i = 0; i <= newPix; i++) {	
			delete system.at(i);													// löschen des Partikel Obj.
			system.erase(system.begin() + i);										//löschen der des Pointer auf Partikel
		}
	}

	//----------------------------------------------------------//Üpdaten der PartiklenBewegung

	if (tornadoIsFinished == true) {												//Bewegung bei Symbolen
		for (int p = 0; p < system.size();) {
			if (p * 7 < attractors.size()) {
				if (symbolAttractorIsSet == false) {
					system.at(p)->updateParticle(deltaT, ofVec2f(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())),
						cloudAttractorIsSet, tornadoIsFinished);					//Partikel werden an beliebige stelle gezogen				
				}
				else
				{
					system.at(p)->updateParticle(deltaT, attractors[p * 7], 
						cloudAttractorIsSet, tornadoIsFinished);					//wie genau wird img gezeichnet(jedes 10. pixel)
				}
			}
			else {
				system.at(p)->updateParticle(deltaT, ofVec2f(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())), 
					
					cloudAttractorIsSet, tornadoIsFinished);						//Partikel werden an beliebige stelle gezogen
			}
			p++;
		}
	}
	else {																			//Bewegung bei Tornado
		for (int p = 0; p < system.size(); p++) {
			particle02* partikel = system.at(p);

			partikel->updateParticle(deltaT, ofVec2f(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())), cloudAttractorIsSet, tornadoIsFinished);

			if (system.at(p)->shallBeKilled()) {
				delete system.at(p);
				system.erase(system.begin() + p);
				p--;
			}
		}
		updateTornado();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	for (int i = 0; i < system.size(); i++) {
		system.at(i)->draw();
		if (tornadoIsFinished == true) {								// damit nicht jeder Bildpkt Partikel bekommt
			if (drawAllPixel == false) {
				i = i + 2;
			}
		}
	}
}

vector<ofVec2f> ofApp::pixelInVector(ofImage a) {						//Einlesen der Farbigen Pixel eines Bildes und umwandeln in Vektoren
	int picWidth = a.getWidth();
	int picHeight = a.getHeight();
	ofPixels pix;
	pix = a.getPixels();
	vector<ofVec2f> pxPos;
	picPix = 0;
	for (int i = 3; i <= pix.size(); i += 4) {
		if (pix[i] > 0) {
			int width = pix.getWidth();

			int y = i / 4 / width;

			int x = i / 4 % width;

			ofVec2f vec;
			vec.set(x + ((ofGetWidth() / 2) - picWidth / 2), y + ((ofGetHeight()) - picHeight));

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
void ofApp::keyReleased(int key) {			
	switch (key) {
	case ' ':												//löshcen von Partikel
		for (int p = 0; p < system.size();) {				
			if (system.at(p)->getAgeNorm() >= 1) {			//schauen ob maxAge erreicht
				delete system.at(p);						// löschen des Partikel Obj.
				system.erase(system.begin() + p);			//löschen der des Pointer auf Partikel
			}
			p++;
		}
		maxParticle = 0;									// damit keine neuen Partikel durch die update-Methode ersellt werden.
		break;
	case 'a':												//Tornado
		startTornado();
		tornadoIsFinished = false;
		break;
	case 'd':
		cloudAttractorIsSet = true;
		tornadoIsFinished = true;
		break;
		//--------------------------------------------------// ab hier laden der unterschiedlichen Bilder
	case '1':												//Bild 1: Ohm
		attractors = pixelInVector(fileImage1);
		symbolAttractorIsSet = true;								
		cloudAttractorIsSet = false;
		tornadoIsFinished = true;
		drawAllPixel = false;
		break;
	case '2':												//Bild 2: Forum-Logo
		attractors = pixelInVector(fileImage2);
		symbolAttractorIsSet = true;								
		cloudAttractorIsSet = false;
		tornadoIsFinished = true;
		drawAllPixel = false;
		break;
	case '3':												//Bild 3: Danke
		attractors = pixelInVector(fileImage3);
		symbolAttractorIsSet = true;								
		cloudAttractorIsSet = false;
		tornadoIsFinished = true;
		drawAllPixel = true;
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
	case 0:															//Status 0: Partikel wandern zur Grenze
		if ((time - tornadoStartTime) > 1.9) {
			status = 1;
			for (int p = 0; p < system.size(); p++) {
				particle02* partikel = system.at(p);
				partikel->startStage1();
			}
		}
		break;
	case 1:															//Status 1: Tornado wandert nach Oben 
		if ((time - tornadoStartTime) > 20) {
			status = -1;											//Status -1: Es "schneit"
		}
		for (int p = 0; p < system.size(); p++) {
			particle02* partikel = system.at(p);
			partikel->updateStage1();
		}
		break;
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