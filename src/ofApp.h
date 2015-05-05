/*
 * ofApp.h
 *
 *  Created on: Jul 19, 2013
 *      Author: arturo castro
 */

#pragma once

#include "ofMain.h"
#include "ofxGstRTPClient.h"
#include "ofxGstRTPServer.h"
#include "ofxGui.h"

#define DO_ECHO_CANCEL 0

#if DO_ECHO_CANCEL
#include "ofxEchoCancel.h"
#endif

class ofApp : public ofBaseApp{

	public:

	    int vW = 1920;
	    int vH = 1080;
	    int cropSizeX = 640;
	    int cropSizeY = 480;
	    int cropPositionX, cropPositionY;
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

		ofxGstRTPClient client1, client2;
		//ofxGstRTPServer server;

		ofVideoGrabber grabber1, grabber2;
		ofTexture texture1, texture2;

		ofxPanel gui;
#if DO_ECHO_CANCEL
		ofxEchoCancel echoCancel;
#endif
};
