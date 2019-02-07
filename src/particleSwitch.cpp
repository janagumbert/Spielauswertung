#include "particleSwitch.h"

particle02::particle02() {
    
}

//--------------------------------------------------------------

particle02::~particle02() {
    
}

//--------------------------------------------------------------

void particle02::setup(ofVec2f pos, float maxAge) {
    
	this->pos = pos; //pointer auf Position ofVec2f position
	vel.set(ofRandom(-20.0, 20.0), ofRandom(90, 100));// ofRandom(-20.0, 20.0));      //Die Bewegungsrichtung

	age = 0.0;              //Alter ist am Anfang 0
	maxLife = ofRandom(maxAge - 5, maxAge);          //Wie lange der Partikel maximal leben soll
	size = ofRandom(0.5, 5);
	mass = ofRandom(100, 200); //verändert die PArtikelgeschwindigkeit
	color.set(0, 178, 255);
    
}

//--------------------------------------------------------------

void particle02::updateParticle(double deltaT, ofVec2f attractor, bool deleteAttractor, bool noAttractor, bool tornadoFinished) {
	if (tornadoFinished == false) {
		pos += vel * deltaT;
		age += deltaT;

		if (pos.x >= ofGetWidth()) {
			pos.x = 0;
		}
	}

//---------------------------------------------------------------
	if (tornadoFinished == true) {
		age += deltaT;
		vel.set(ofRandom(-20.0, 20.0), 0);
		ofVec2f force = attractor - pos; //Anziehungskraft

		if (force.length() < 200) {   //force.length = abstand (partikel - attractor)
			force = 30 * force;//.getNormalized();  //  Anziehungskraft des Attraktors auf die Partikel
		}
		else {
			force = 10 * force.getNormalized(); //wie stark werden die partikel zu img gezogen

		};

		vel += force;  // Bewegung zum attraktor
		vel = mass * vel.getNormalized(); //bleiben sonst nicht an attractor kleben 
		pos += (vel * deltaT); //position = m/s * s [partikel bleiben statisch/bewegen sich nicht ohne]

		if (deleteAttractor == true) {
			attractor.set((ofRandom(0, ofGetWidth())), ofRandom(0, ofGetHeight() / 8));	//Attraktor wird neu gesetzt !!!!!!!!!!!!!!!!!!!!!!!
			ofVec2f force2 = attractor - pos;

			velocity2 += force2 / 50;  // Bewegung zum Attraktor
			velocity2 = (mass / 12)* velocity2.getNormalized(); //Bewegungsgeschwindigkeit hin zum Attraktor
			pos += (velocity2) * 2; //position = m/s Partikel bleiben nicht statisch am attractor kleben		
		}

		if (noAttractor == true) {
			attractor.set((ofRandom(0, ofGetWidth())), ofRandom(0, ofGetHeight()));
			ofVec2f force2 = attractor - pos;

			velocity2 += force2 / 5;  // Bewegung zum Attraktor
			velocity2 = (mass / 12)* velocity2.getNormalized(); //Bewegungsgeschwindigkeit hin zum Attraktor
			pos += (velocity2) * 2; //position = m/s Partikel bleiben nicht statisch am attractor kleben		
		}
	}

}





//--------------------------------------------------------------

void particle02::draw() {
    ofSetColor(this->color);
    ofDrawCircle(pos , size);    
}


//--------------------------------------------------------------

void particle02::startTornado() {
//    status = 0;
    int distance = pos.y - ofGetHeight()/3.5*3;
    vel.y = -distance/2;
}

//--------------------------------------------------------------

void particle02::startStage1() {
    vel.y = ofRandom(10, 25)*(-1);
}

//--------------------------------------------------------------

void particle02::updateStage1() {
    vel += ofVec2f(ofRandom(2,2.5), ofRandom(0.2, 0.3)*(-1));
    color = ofColor::red;
    float hue = ofMap( age, 100, maxLife, 155, 255 );
    color.setHue( hue );
    ofSetColor(color, (1 - age/maxLife)*255 );
}

//--------------------------------------------------------------

float particle02::getAgeNorm() {
    return age/maxLife;
}

//--------------------------------------------------------------

float particle02::shallBeKilled() {
    return pos.y < 0 || pos.y > ofGetHeight();
    
}
