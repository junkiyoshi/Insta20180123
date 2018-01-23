#pragma once
#include "ofMain.h"

class Particle
{
public:
	Particle();
	~Particle() {};

	void apply_force(ofVec2f force);
	void update();
	void draw();

	void set_color(ofColor body_color);
	ofVec2f get_location();
	ofColor get_body_color();

private:
	ofVec2f location;
	ofVec2f velocity;
	ofVec2f acceleration;
	ofColor body_color;
};