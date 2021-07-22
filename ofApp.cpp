#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->font_size = 80;
	this->font.loadFont("fonts/Kazesawa-Bold.ttf", this->font_size, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);

	string word = "ABCDEFGHEJKLMNOPQRSTUVWXYZ!";
	int sample_count = 30;
	int span = 300;
	vector<glm::vec3> base_location = {
		glm::vec3(-350, -350, 0), glm::vec3(350, -350, 0),
		glm::vec3(-350, 350, 0), glm::vec3(350, 350, 0),
	};

	for (int k = 0; k < base_location.size(); k++) {

		for (int radius = 100; radius <= 300; radius += 100) {

			auto noise_param = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
			for (int i = 0; i < word.size(); i++) {

				ofPath chara_path = this->font.getCharacterAsPoints(word[i], true, false);
				vector<ofPolyline> outline = chara_path.getOutline();

				ofFill();
				ofSetColor(239);
				ofBeginShape();
				for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

					if (outline_index != 0) { ofNextContour(true); }

					auto vertices = outline[outline_index].getResampledByCount(sample_count).getVertices();
					for (auto& vertex : vertices) {

						auto location = vertex - glm::vec3(this->font_size * 0.5, this->font_size * -0.5, 320);
						auto rotation = glm::rotate(glm::mat4(), (i * 13.5f) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
						location = glm::vec4(location, 0) * rotation;

						auto noise_location = glm::vec4(this->font_size * 0.5, this->font_size * -0.5, 320, 0) * rotation;
						auto angle_x = ofMap(ofNoise(noise_param.x, noise_location.x * 0.0005, ofGetFrameNum() * 0.01), 0, 1, -PI * 1.5, PI * 1.5);
						auto angle_y = ofMap(ofNoise(noise_param.x, noise_location.y * 0.0005, ofGetFrameNum() * 0.01), 0, 1, -PI * 1.5, PI * 1.5);
						auto angle_z = ofMap(ofNoise(noise_param.x, noise_location.z * 0.0005, ofGetFrameNum() * 0.01), 0, 1, -PI * 1.5, PI * 1.5);

						auto rotation_x = glm::rotate(glm::mat4(), angle_x, glm::vec3(1, 0, 0));
						auto rotation_y = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));
						auto rotation_z = glm::rotate(glm::mat4(), angle_z, glm::vec3(0, 0, 1));

						location = glm::vec4(location, 0) * rotation_z * rotation_y * rotation_x;
						location = glm::normalize(location) * radius;
						location += base_location[k];

						ofVertex(location);
					}
				}
				ofEndShape();

				ofNoFill();
				ofSetColor(39);
				ofBeginShape();
				for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

					if (outline_index != 0) { ofNextContour(true); }

					auto vertices = outline[outline_index].getResampledByCount(sample_count).getVertices();
					for (auto& vertex : vertices) {

						auto location = vertex - glm::vec3(this->font_size * 0.5, this->font_size * -0.5, 320);
						auto rotation = glm::rotate(glm::mat4(), (i * 13.5f) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
						location = glm::vec4(location, 0) * rotation;

						auto noise_location = glm::vec4(this->font_size * 0.5, this->font_size * -0.5, 320, 0) * rotation;
						auto angle_x = ofMap(ofNoise(noise_param.x, noise_location.x * 0.0005, ofGetFrameNum() * 0.01), 0, 1, -PI * 1.5, PI * 1.5);
						auto angle_y = ofMap(ofNoise(noise_param.x, noise_location.y * 0.0005, ofGetFrameNum() * 0.01), 0, 1, -PI * 1.5, PI * 1.5);
						auto angle_z = ofMap(ofNoise(noise_param.x, noise_location.z * 0.0005, ofGetFrameNum() * 0.01), 0, 1, -PI * 1.5, PI * 1.5);

						auto rotation_x = glm::rotate(glm::mat4(), angle_x, glm::vec3(1, 0, 0));
						auto rotation_y = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));
						auto rotation_z = glm::rotate(glm::mat4(), angle_z, glm::vec3(0, 0, 1));

						location = glm::vec4(location, 0) * rotation_z * rotation_y * rotation_x;
						location = glm::normalize(location) * radius;
						location += base_location[k];

						ofVertex(location);
					}
				}
				ofEndShape();
			}
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}