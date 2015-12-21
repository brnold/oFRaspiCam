#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(66,66,66);

	image.loadImage("small.jpg");
	
	//initialize the video grabber
	//image.setVerbose(true);
	//image.initGrabber(320,240);

	//store the width and height for convenience
	int width = image.getWidth();
	int height = image.getHeight();
	
	//add one vertex to the mesh for each pixel
	for (int y = 0; y < height; y++){
		for (int x = 0; x<width; x++){
			mainMesh.addVertex(ofPoint(x,y,0));	// mesh index = x + y*width
												// this replicates the pixel array within the camera bitmap...
			mainMesh.addColor(ofFloatColor(0,0,0));  // placeholder for colour data, we'll get this from the camera
		}
	}
	
	for (int y = 0; y<height-1; y++){
		for (int x=0; x<width-1; x++){
			mainMesh.addIndex(x+y*width);				// 0
			mainMesh.addIndex((x+1)+y*width);			// 1
			mainMesh.addIndex(x+(y+1)*width);			// 10
			
			mainMesh.addIndex((x+1)+y*width);			// 1
			mainMesh.addIndex((x+1)+(y+1)*width);		// 11
			mainMesh.addIndex(x+(y+1)*width);			// 10
		}
	}
	
	//this is an annoying thing that is used to flip the camera
	cam.setScale(1,-1,0.4);


	sphere.setRadius(140);
	
	//this determines how much we push the meshes out
	extrusionAmount = 1;
}

//--------------------------------------------------------------
void ofApp::update(){
	//grab a new frame
	//image.update();
	
	//update the mesh if we have a new frame
	if (true){
		//this determines how far we extrude the mesh
		for (int i=0; i<image.getWidth()*image.getHeight(); i++){

			ofFloatColor sampleColor(image.getPixels()[i*3]/255.f,				// r
									 image.getPixels()[i*3+1]/255.f,			// g
									 image.getPixels()[i*3+2]/255.f);			// b
			
			//now we get the vertex aat this position
			//we extrude the mesh based on it's brightness
			ofVec3f tmpVec = mainMesh.getVertex(i);
			tmpVec.z = sampleColor.getBrightness() * extrusionAmount;
			mainMesh.setVertex(i, tmpVec);

			mainMesh.setColor(i, sampleColor);
		}
	}
	
	//let's move the camera when you move the mouse
	float rotateAmount = ofMap(ofGetMouseX(), 0, ofGetWidth()-100, -180, 180);

	
	//move the camera around the mesh
	ofVec3f camDirection(0,0.4,1);
	ofVec3f centre(image.getWidth()/2.f,image.getHeight()/2.f, 255/2.f);
	ofVec3f camDirectionRotated = camDirection.rotated(rotateAmount, ofVec3f(1,0,0));
	ofVec3f camPosition = centre + camDirectionRotated * extrusionAmount;
	//ofVec3f camPosition = centre * extrusionAmount;
	

	cam.setPosition(camPosition);
	cam.lookAt(centre);
}

//--------------------------------------------------------------
void ofApp::draw(){
	//we have to disable depth testing to draw the video frame
	//ofDisableDepthTest();
//	image.draw(20,20);
	
	//but we want to enable it to show the mesh
	ofEnableDepthTest();
	sphere.setPosition(ofGetWidth()*.2, ofGetHeight()*.75, 0);
	ofSetColor(123,123,11);
	sphere.draw();
	cam.begin();		

	//You can either draw the mesh or the wireframe
	// mainMesh.drawWireframe();
	mainMesh.drawFaces();
	cam.end();
	
	//draw framerate for fun
	ofSetColor(255);
	string msg = "fps: " + ofToString(ofGetFrameRate(), 2);
	ofDrawBitmapString(msg, 10, 20);
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key) {
		case 'f':
			ofToggleFullscreen();
			break;
	}

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::exit(){ 

}

