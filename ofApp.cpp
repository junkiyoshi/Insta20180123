#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofBackground(0);
	ofSetWindowTitle("Insta");

	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	ofSetLineWidth(1.3);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 250, true, false, true);
	this->words = "YES";
	this->words_size = ofPoint(this->font.stringWidth(this->words), this->font.stringHeight(this->words));
	this->paths = this->font.getStringAsPoints(this->words);

	for (int i = 0; i < 512; i++) {

		unique_ptr<Particle> particle(new Particle());
		this->particles.push_back(std::move(particle));
	}

	this->fbo.allocate(ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::update() {

	this->fbo.begin();
	ofClear(0);
	
	for (int i = 0; i < this->particles.size(); i++) {

		this->particles[i]->update();
	}

	for (int p_index = 0; p_index < this->paths.size(); p_index++) {

		vector<ofPolyline> outline = this->paths[p_index].getOutline();
		for (int o_index = 0; o_index < outline.size(); o_index++) {

			outline[o_index] = outline[o_index].getResampledBySpacing(15);
			vector<ofPoint> vertices = outline[o_index].getVertices();
			for (int v_index = 0; v_index < vertices.size(); v_index++) {

				ofPoint point = vertices[v_index] + ofPoint(ofGetWidth() / 2, ofGetHeight() / 2) - ofPoint(this->words_size.x / 2, -this->words_size.y / 2);
				for (int i = 0; i < this->particles.size(); i++) {

					float distance = this->particles[i]->get_location().distance(point);
					if (distance < 80) {

						ofSetColor(this->particles[i]->get_body_color(), ofMap(distance, 0, 80, 255, 0));
						ofDrawLine(point, this->particles[i]->get_location());
					}
				}
			}
		}
	}

	this->fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->fbo.draw(0, 0);
}

//========================================================================
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}