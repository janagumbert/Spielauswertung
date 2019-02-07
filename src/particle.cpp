#include "particle.h"

theParticle::theParticle() {

}

theParticle::~theParticle() {

}

void theParticle::setup(ofVec2f position, float maxAge) {
	this->position = position; //pointer auf Position ofVec2f position
	velocity.set(ofRandom(-20.0, 20.0), 0);// ofRandom(-20.0, 20.0));      //Die Bewegungsrichtung

	age = 0.0;              //Alter ist am Anfang 0
	maxLife = ofRandom(maxAge-5, maxAge);          //Wie lange der Partikel maximal leben soll
	size = ofRandom(0.5, 5);
	mass = ofRandom(100, 200); //verändert die PArtikelgeschwindigkeit
	color.set(0, 178, 255);
}

void theParticle::update(float deltaT, ofVec2f attractor, bool deleteAttractor, bool noAttractor) //deltaT ist die Zeitintervall seit dem letzte Update
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
	position += (velocity * deltaT); //position = m/s * s [partikel bleiben statisch/bewegen sich nicht ohne]

	if (deleteAttractor == true){
		attractor.set((ofRandom(0, ofGetWidth())), ofRandom(0, ofGetHeight() / 8));	//Attraktor wird neu gesetzt !!!!!!!!!!!!!!!!!!!!!!!
		ofVec2f force2 = attractor - position;	

		velocity2 += force2 / 50;  // Bewegung zum Attraktor
		velocity2 = (mass / 12)* velocity2.getNormalized(); //Bewegungsgeschwindigkeit hin zum Attraktor
		position += (velocity2)*2; //position = m/s Partikel bleiben nicht statisch am attractor kleben		
	}

	if (noAttractor == true) {
		attractor.set((ofRandom(0, ofGetWidth())), ofRandom(0, ofGetHeight()));
		ofVec2f force2 = attractor - position;

		velocity2 += force2 / 5;  // Bewegung zum Attraktor
		velocity2 = (mass / 12)* velocity2.getNormalized(); //Bewegungsgeschwindigkeit hin zum Attraktor
		position += (velocity2) * 2; //position = m/s Partikel bleiben nicht statisch am attractor kleben		
	}
}

void theParticle::draw() {
	ofSetColor(color);
	ofDrawCircle(position, size);
}


float theParticle::getAgeNorm() {
	return age / maxLife;
}