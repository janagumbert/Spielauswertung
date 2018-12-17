#include "particle.h"

theParticle::theParticle() {

}

theParticle::~theParticle() {

}

void theParticle::setup(ofVec2f position) {
	this->position = position; //pointer auf Position ofVec2f position
	velocity.set(ofRandom(-20.0, 20.0), ofRandom(-20.0, 20.0));      //Die Bewegungsrichtung

	age = 0.0;              //Alter ist am Anfang 0
	maxLife = 10.0;          //Wie lange der Partikel maximal leben soll

	size = ofRandom(0.5,3);
	mass = ofRandom(100, 200); //verändert die PArtikelgeschwindigkeit

	color.set(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255));
}


void theParticle::update(float deltaT, ofVec2f attractor) //deltaT ist die Zeitintervall seit dem letzte Update
{
	age += deltaT;

	ofVec2f force = attractor - position; //Anziehungskraft


	if (force.length() < 200) {   //force.length = abstand (partikel - attractor)
		force = 30 * force;//.getNormalized();  //  Anziehungskraft des Attraktors auf die Partikel
	}
	else {
		force = 10 * force.getNormalized(); //wie stark werden die partikel zu img gezogen
		
	};


	velocity += force;  // Bewegung zum attraktor
	velocity = mass * velocity.getNormalized(); //bleiben sonst nicht an attractor kleben 
	position += (velocity * deltaT); //position = m/s * s [partikel bleiben statisch/bewegen sich nciht ohne]

	if (age >= maxLife) {
		attractor.set((ofRandom(0,ofGetWidth())), 0);
		ofVec2f force = attractor - position;
		//color.set(ofColor(255, 150, 150));  //nach gewisser lebenszeit wird farbe geändert
	
		velocity += force;  // Bewegung zum attraktor
		velocity = mass * velocity.getNormalized(); //bleiben sonst nicht an attractor kleben 
		position += (velocity * deltaT); //position = m/s * s [partikel bleiben statisch/bewegen sich nciht ohne]

	}

	
}

void theParticle::draw() {

	ofSetColor(color);
	ofDrawCircle(position, size);
}
//
//float theParticle::getAgeNorm() {
//	return age / maxLife;
//}