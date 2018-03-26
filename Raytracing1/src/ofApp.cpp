#include "ofApp.h"

#include <iostream>
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"
#include "material.h"
#include "util.h"

#define M_PI 3.14159265358979323846

//--------------------------------------------------------------
void ofApp::setup(){
	nx = ofGetWidth();
	ny = ofGetHeight();
	ns = 10;

	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	hitable *list[5];
	float R = cos(M_PI / 4);
	list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));
	list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
	list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.0));
	list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));
	list[4] = new sphere(vec3(-1, 0, -1), -0.45, new dielectric(1.5));
	hitable *world = new hitable_list(list, 5);
	world = random_scene();

	vec3 lookfrom(13, 2, 3);
	vec3 lookat(0, 0, 0);
	float dist_to_focus = 10.0;
	float aperture = 0.1;

	camera cam(lookfrom, lookat, vec3(0, 1, 0), 20, float(nx) / float(ny), aperture, dist_to_focus);

	percentCounter = 0;
	renderedPixels.allocate(nx, ny, OF_PIXELS_RGBA);

	for (int j = 0; j < ny; j++) {
		for (int i = 0; i < nx; i++) {
			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++) {
				float u = float(i + drand48()) / float(nx);
				float v = 1.0 - float(j + drand48()) / float(ny);
				ray r = cam.get_ray(u, v);
				vec3 p = r.point_at_parameter(2.0);
				col += color(r, world, 0);
			}
			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

			col[0] *= 255.99;
			col[1] *= 255.99;
			col[2] *= 255.99;

			renderedPixels.setColor(i, j, ofColor(col[0], col[1], col[2]));

			int loc = i + j * nx;
			std::cout << "RENDERING ";
			if (loc % 2 == 0) {
				std::cout << " . ";
			}
			else if (loc % 3 == 0) {
				std::cout << "  .";
			}
			else {
				std::cout << ".  ";
			}
			std::cout << " completed: " << int((percentCounter / (float)(ny * nx)) * 100.0) << "% ";
			if (loc % 2 == 0) {
				std::cout << " . ";
			}
			else if (loc % 3 == 0) {
				std::cout << ".  ";
			}
			else {
				std::cout << "  .";
			}
			std::cout << " color: (" << int(col[0]) << ", " << int(col[1]) << ", " << int(col[2]) << ") \n";
			percentCounter++;
		}
	}
	std::cout << "RENDERING ... completed: 100%";

	rendered = shared_ptr<ofTexture>(new ofTexture);
	rendered->allocate(renderedPixels);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(128, 128, 128);
	ofSetColor(255, 255, 255, 255);

	rendered->draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

