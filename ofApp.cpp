#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	int radius = 300;
	int theta = 90;

	for (int z = -300; z <= 300; z += 20) {

		auto noise_value = ofNoise(z * 0.0025, ofGetFrameNum() * 0.01);
		auto phi_len = ofMap(noise_value, 0, 1, -180, 360 * 1.52);
		if (phi_len > 360) { phi_len = 360; }
		if (phi_len < 3) { phi_len = 3; }

		for (int phi = 0; phi < phi_len; phi += 3) {

			auto index = this->face.getNumVertices();
			vector<glm::vec3> vertices;

			vertices.push_back(glm::vec3(
				radius * cos(phi * DEG_TO_RAD) * sin((theta + 1) * DEG_TO_RAD),
				radius * sin(phi * DEG_TO_RAD) * sin((theta + 1) * DEG_TO_RAD),
				radius * cos((theta + 1) * DEG_TO_RAD)
			));
			vertices.push_back(glm::vec3(
				radius * cos((phi + 3) * DEG_TO_RAD) * sin((theta + 1) * DEG_TO_RAD),
				radius * sin((phi + 3) * DEG_TO_RAD) * sin((theta + 1) * DEG_TO_RAD),
				radius * cos((theta + 1) * DEG_TO_RAD)
			));
			vertices.push_back(glm::vec3(
				radius * cos((phi + 3) * DEG_TO_RAD) * sin((theta - 1) * DEG_TO_RAD),
				radius * sin((phi + 3) * DEG_TO_RAD) * sin((theta - 1) * DEG_TO_RAD),
				radius * cos((theta - 1) * DEG_TO_RAD)
			));
			vertices.push_back(glm::vec3(
				radius * cos(phi * DEG_TO_RAD) * sin((theta - 1) * DEG_TO_RAD),
				radius * sin(phi * DEG_TO_RAD) * sin((theta - 1) * DEG_TO_RAD),
				radius * cos((theta - 1) * DEG_TO_RAD)
			));

			vertices.push_back(glm::vec3(
				(radius - 30) * cos(phi * DEG_TO_RAD) * sin((theta + 1) * DEG_TO_RAD),
				(radius - 30) * sin(phi * DEG_TO_RAD) * sin((theta + 1) * DEG_TO_RAD),
				radius * cos((theta + 1) * DEG_TO_RAD)
			));
			vertices.push_back(glm::vec3(
				(radius - 30) * cos((phi + 3) * DEG_TO_RAD) * sin((theta + 1) * DEG_TO_RAD),
				(radius - 30) * sin((phi + 3) * DEG_TO_RAD) * sin((theta + 1) * DEG_TO_RAD),
				radius * cos((theta + 1) * DEG_TO_RAD)
			));
			vertices.push_back(glm::vec3(
				(radius - 30) * cos((phi + 3) * DEG_TO_RAD) * sin((theta - 1) * DEG_TO_RAD),
				(radius - 30) * sin((phi + 3) * DEG_TO_RAD) * sin((theta - 1) * DEG_TO_RAD),
				radius * cos((theta - 1) * DEG_TO_RAD)
			));
			vertices.push_back(glm::vec3(
				(radius - 30) * cos(phi * DEG_TO_RAD) * sin((theta - 1) * DEG_TO_RAD),
				(radius - 30) * sin(phi * DEG_TO_RAD) * sin((theta - 1) * DEG_TO_RAD),
				radius * cos((theta - 1) * DEG_TO_RAD)
			));

			for (auto& vertex : vertices) {

				vertex += glm::vec3(0, 0, z);
			}

			auto frame_index = this->frame.getNumVertices();

			this->face.addVertices(vertices);
			this->frame.addVertices(vertices);

			this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 2);
			this->face.addIndex(index + 0); this->face.addIndex(index + 2); this->face.addIndex(index + 3);

			this->face.addIndex(index + 4); this->face.addIndex(index + 5); this->face.addIndex(index + 6);
			this->face.addIndex(index + 4); this->face.addIndex(index + 6); this->face.addIndex(index + 7);

			this->face.addIndex(index + 0); this->face.addIndex(index + 4); this->face.addIndex(index + 5);
			this->face.addIndex(index + 0); this->face.addIndex(index + 5); this->face.addIndex(index + 1);

			this->face.addIndex(index + 2); this->face.addIndex(index + 6); this->face.addIndex(index + 7);
			this->face.addIndex(index + 2); this->face.addIndex(index + 7); this->face.addIndex(index + 3);

			this->frame.addIndex(index + 0); this->frame.addIndex(index + 1);
			this->frame.addIndex(index + 2); this->frame.addIndex(index + 3);

			this->frame.addIndex(index + 4); this->frame.addIndex(index + 5);
			this->frame.addIndex(index + 6); this->frame.addIndex(index + 7);

			for (int i = 0; i < vertices.size(); i++) {

				this->face.addColor(ofColor(39));
				this->frame.addColor(ofColor(239));
			}

			if (phi == 0 && phi_len < 360) {

				this->frame.addIndex(frame_index + 0); this->frame.addIndex(frame_index + 3);
				this->frame.addIndex(frame_index + 0); this->frame.addIndex(frame_index + 4);
				this->frame.addIndex(frame_index + 7); this->frame.addIndex(frame_index + 3);
				this->frame.addIndex(frame_index + 7); this->frame.addIndex(frame_index + 4);

			}
		}

		if (phi_len < 360) {

			auto frame_index = this->frame.getNumVertices() - 8;

			this->frame.addIndex(frame_index + 1); this->frame.addIndex(frame_index + 2);
			this->frame.addIndex(frame_index + 1); this->frame.addIndex(frame_index + 5);
			this->frame.addIndex(frame_index + 6); this->frame.addIndex(frame_index + 2);
			this->frame.addIndex(frame_index + 6); this->frame.addIndex(frame_index + 5);
		}
	}
}


//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);
	ofRotateY(90);

	this->face.draw();
	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}