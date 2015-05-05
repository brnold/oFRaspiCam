#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){

    ofSetLogLevel(OF_LOG_VERBOSE);


	ofAppGlutWindow window; // create a window
	ofSetupOpenGL(&window, 640+300+640,480,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());



            // set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
            //ofSetupOpenGL(&window, 1280,720, OF_WINDOW);
            //ofRunApp(new testApp()); // start the app
}
