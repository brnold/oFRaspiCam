/*
 * ofApp.h
 *
 *  Created on: Jul 19, 2013
 *      Author: Benjamin Nold
 */

#pragma once

#include "ofMain.h"
//#include "ofxGui.h"


#define STATIC_IMAGE 1

class ofApp : public ofBaseApp{

	public:


		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);


		ofSpherePrimitive sphere;

		
	
	ofCamera cam; // add mouse controls for camera movement
	float extrusionAmount;
	ofVboMesh mainMesh;
	//ofVideoGrabber vidGrabber;
	ofImage image;

};
