#include "particleSwitch.h"

particle02::particle02() {
    
}

//--------------------------------------------------------------

particle02::~particle02() {
    
}

//--------------------------------------------------------------

void particle02::setup(ofVec2f pos, float maxAge) {
    
    this->pos = pos;
    vel.set(ofRandom(-40, 40), ofRandom(90,100));
    color = 255;
//    color = ofColor::goldenRod;
    age = 0.0;
    maxLife = 20.0;
    
    size = ofRandom(0.5,5);
    
}

//--------------------------------------------------------------

void particle02::updateParticle(double deltaT, ofVec2f attractor, bool deleteAttractor, bool noAttractor, bool tornadoFinished) {
    pos += vel * deltaT;
    age += deltaT;
    
    if (pos.x >= ofGetWidth()) {
        pos.x = 0;
    }

//---------------------------------------------------------------
	if (tornadoFinished == true) {
		age += deltaT;

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
    ofSetColor(this->color /*, (1 - age/maxLife)*255*/ );
    ofDrawCircle(pos , size);
    //        ofDrawCircle(pos.x, pos.y , size);
    //    float yPos = ofMap(sin(ofGetElapsedTimef()), -1, 1, 0, ofGetWidth());
    //    ofRect(ofGetWidth()/2, 10,10, yPos);
    
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
