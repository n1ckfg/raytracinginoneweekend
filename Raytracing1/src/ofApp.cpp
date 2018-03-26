#include "ofApp.h"

#include <iostream>
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"
#include "material.h"
#include "util.h"

//#define M_PI 3.14159265358979323846

hitable *hitList[5];
hitable *worldList;
vec3 lookfrom(13, 2, 3);
vec3 lookat(0, 0, 0);
float dist_to_focus = 10.0;
float aperture = 0.1;
int nx;
int ny;
int ns = 10; // samples
int lineCounter = 0;

//--------------------------------------------------------------
void ofApp::setup() {
	nx = ofGetWidth();
	ny = ofGetHeight();

	//std::cout << "P3\n" << nx << " " << ny << "\n255\n";

	hitList[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));
	hitList[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
	hitList[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.0));
	hitList[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));
	hitList[4] = new sphere(vec3(-1, 0, -1), -0.45, new dielectric(1.5));

	hitable *world = new hitable_list(hitList, 5);
	worldList = random_scene();

	renderedPixels.allocate(nx, ny, OF_PIXELS_RGBA);
	rendered = shared_ptr<ofTexture>(new ofTexture);
}

//--------------------------------------------------------------
void ofApp::update() {
	if (lineCounter < ny) {
		camera cam(lookfrom, lookat, vec3(0, 1, 0), 20, float(nx) / float(ny), aperture, dist_to_focus);
		
		//hitable *list[5];
		//float R = cos(M_PI / 4);

		int j = lineCounter;

		for (int i = 0; i < nx; i++) {
			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++) {
				float u = float(i + drand48()) / float(nx);
				float v = 1.0 - float(j + drand48()) / float(ny);
				ray r = cam.get_ray(u, v);
				vec3 p = r.point_at_parameter(2.0);
				col += color(r, worldList, 0);
			}
			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

			col[0] *= 255.99;
			col[1] *= 255.99;
			col[2] *= 255.99;

			renderedPixels.setColor(i, j, ofColor(col[0], col[1], col[2]));
		}

		rendered->allocate(renderedPixels);

		if (lineCounter == ny - 1) {
			ofImage img;
			img.setFromPixels(renderedPixels);
			img.save("render.png");

			std::cout << "_____________________________\n";
			std::cout << "RENDERING ... completed: 100%\n";
		} else {
			std::cout << "RENDERING ";
			if (lineCounter % 2 == 0) {
				std::cout << " . ";
			}
			else if (lineCounter % 3 == 0) {
				std::cout << "  .";
			}
			else {
				std::cout << ".  ";
			}

			std::cout << " completed: " << int(((float)lineCounter / (float)ny) * 100.0) << "%\n";
		}

		lineCounter++;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(0);
	rendered->draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {

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

