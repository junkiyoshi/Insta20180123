#include "Particle.h"

Particle::Particle() {

	this->location = ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
	this->velocity = ofVec2f(ofRandom(-3, 3), ofRandom(-3, 3));
	this->velocity = this->velocity.normalized() * ofRandom(1, 3);
	this->acceleration = ofVec2f();
	this->body_color.setHsb(ofRandom(255), 255, 255);
}

void Particle::apply_force(ofVec2f force) {

	this->acceleration += force;
}

void Particle::update() {

	this->acceleration += this->velocity;
	this->location += this->acceleration;
	this->acceleration *= 0;

	if (this->location.x < 0) {

		this->location.x = 0;
		this->velocity.x *= -1;
	}
	else if (this->location.x > ofGetWidth()) {

		this->location.x = ofGetWidth();
		this->velocity.x *= -1;
	}

	if (this->location.y < 0) {

		this->location.y = 0;
		this->velocity.y *= -1;
	}
	else if (this->location.y > ofGetHeight()) {

		this->location.y = ofGetHeight();
		this->velocity.y *= -1;
	}
}

void Particle::draw() {

	ofSetColor(this->body_color);
	ofDrawCircle(this->location, 3);
}

void Particle::set_color(ofColor body_color) {
	
	this->body_color = body_color;
}

ofVec2f Particle::get_location() {

	return this->location;
}

ofColor Particle::get_body_color() {

	return this->body_color;
}