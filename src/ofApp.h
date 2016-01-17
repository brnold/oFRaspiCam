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
#include "ofxOculusDK2.h"
//#include "ofxGui.h"

#define DO_ECHO_CANCEL 0

#if DO_ECHO_CANCEL
#include "ofxEchoCancel.h"
#endif

#define STATIC_IMAGE 1
#define VIDEO 0 

#define OCULUS_YAH 1




class ofApp : public ofBaseApp{

	public:

		//static inmage crap
		int w, h;
		unsigned char * picPixels;	
		//end crap


		ofMesh quad;
		int vW;
	    int vH;
	    int cropSizeX;
	    int cropSizeY;
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

		void drawSceneImage();
		void drawSceneVideo(int side);

		ofxGstRTPClient client1, client2;
		//ofxGstRTPServer server;


		ofVideoGrabber grabber1, grabber2;
		ofTexture texture1, texture2;
		ofImage ofLogo;

		ofxOculusDK2		oculusRift;
		ofEasyCam cam;		
#if DO_ECHO_CANCEL
		ofxEchoCancel echoCancel;
#endif
};
