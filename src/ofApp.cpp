#include "ofApp.h"

//-------------------------------------------------------------


void ofApp::setup(){

	vW = 1920;
	vH = 1080;
	cropSizeX = 640;
	cropSizeY = 480;


#if OCULUS_YAH
	oculusRift.baseCamera = &cam; //attach to your camera
    //opens the device, an Oculus must be plugged in 
    //as it uses the params returned from the head set to configure 
    //the resolution settings
    oculusRift.setup();

#endif

 
	ofSetVerticalSync(true);
	
	// this uses depth information for occlusion
	// rather than always drawing things on top of each other
	ofEnableDepthTest();

	ofEnableNormalizedTexCoords();
	
	// this sets the camera's distance from the object
	cam.setDistance(100);


    ofSetFrameRate(75);

//#if VIDEO //so Video
	//for the cameras

	grabber1.initGrabber(vW,vH);
	grabber2.initGrabber(vW,vH);

	texture1.allocate(vW,vH,GL_RGB);
	texture2.allocate(vW,vH,GL_RGB);
#if VIDEO
	client1.setup(10);
	client1.addVideoChannel(5000);
	client2.setup(10);
	client2.addVideoChannel(6000);
	client1.play();
	client2.play();

#endif

#if STATIC_IMAGE //so Image

	ofLogo.loadImage("photo.jpg");
	w = (int)ofLogo.getWidth();
	h = (int)ofLogo.getHeight();

	
	texture1.allocate(w,h,GL_RGB);
	ofLoadImage(texture1, "photo.jpg");
	//texture1.loadData(picPixels, w, h, GL_RGB);

	texture2.allocate(w,h,GL_RGB);
	ofLoadImage(texture2, "photo.jpg");
#endif	
	
	

	
	

	// to run this example sending data from different applications or computers
	// set the ports to be different in the client and server, but matching the client
	// and server ports from one app to the other, for example one computer will have:
	//
	// client video: 5000
	// client audio: 6000
	// server video: 7000
	// server audio: 8000
	//
	// the other:
	//
	// client video: 7000
	// client audio: 8000
	// server video: 5000
	// server audio: 6000
	//
	// port numbers have to be even according to the standard and have to be separated by at least
	// 4 numbers since internally rtp uses the next 2 odd port numbers for communicating stats
	// of the network state through rctp, so if we set 5000 for video internally it'll use
	// also 5001 and 5003


#if DO_ECHO_CANCEL
	// if echo cancel is enabled we need to setup the echo cancel module and pass it to
	// the server and client, also the server needs a reference to the client in order to now
	// the audio latency to be able to remove the echo
	echoCancel.setup();
	client.setEchoCancel(echoCancel);
	server.setEchoCancel(echoCancel);
	server.setRTPClient(client);
#endif

	// this sets the remote ip and the latency, in a LAN you can usually use latency 0
	// over internet you'll probably need to make it higher, around 200 is usually a good
	// number but depends on the network conditions

	//client.addAudioChannel(6000);
/* 
	server.setup("127.0.0.1");
	server.addVideoChannel(5000,640,480,30);
	server.addAudioChannel(6000);

	gui.setup("Awesome Gui","settings.xml",640+640+20,10);
	gui.add(client1.parameters);
	gui.add(client2.parameters);
	//gui.add(server.parameters);
*/
#if DO_ECHO_CANCEL
	gui.add(echoCancel.parameters);
#endif

}


void ofApp::exit(){

}


//--------------------------------------------------------------
void ofApp::update(){

#if VIDEO

	/* code */

	grabber1.update();
	grabber2.update();
	//if(grabber.isFrameNew()){
	//	server.newFrame(grabber.getPixelsRef());
	//}

	client1.update();
	client2.update();
	
	if(!STATIC_IMAGE){
		if(client1.isFrameNewVideo()){
			texture1.loadData(client1.getPixelsVideo());
		}

		if(client2.isFrameNewVideo()){
			texture2.loadData(client2.getPixelsVideo());
		}
	}
#endif

}

//--------------------------------------------------------------


void ofApp::draw(){
	//move your camera wherever you'd like, this becomes the base
    //position of the view
	

	cam.begin();
    //cam.end();
    //now render using oculus flow
   
   
    
    oculusRift.beginLeftEye();
    
    drawSceneVideo(0);

    oculusRift.endLeftEye();

    oculusRift.beginRightEye();
   
    drawSceneVideo(1);  

    oculusRift.endRightEye();

    cam.end();

    //pushes the render texture to the viewer
   oculusRift.draw();
}

void ofApp::drawSceneVideo(int side){
	float movementSpeed = .1;
	float maxBoxSize = 100;
	float spacing = 1;
	int boxCount = 1;

	//ofBackground(74, 88, 150);

	ofPushMatrix();
	
	float t = 0;
	ofVec3f pos(
		ofSignedNoise(t, 0, 0),
		ofSignedNoise(0, t, 0),
		ofSignedNoise(0, 0, t));
	
	float boxSize = 251;
	
	
	ofTranslate(pos);
	ofRotateX(pos.x);
	ofRotateY(pos.y);
	ofRotateZ(pos.z);
	
	if(side == 0){ // left eye
		texture1.bind();
	ofFill();
	//ofSetColor(255);
	ofDrawBox(0,0,0,boxSize,boxSize, 0);
	texture1.unbind();
	}else{ //right eye

	texture2.bind();
	ofFill();
	//ofSetColor(255);
	ofDrawBox(0,0,0,boxSize,boxSize, 0);
	texture2.unbind();
	}	
	
	//ofNoFill();
	//ofSetColor(ofColor::fromHsb(sinf(t) * 128 + 128, 255, 255));
	//ofDrawBox(boxSize * 1.1f);
	
	ofPopMatrix();
}

void ofApp::drawSceneImage(){

	
	float movementSpeed = .1;
	float maxBoxSize = 100;
	float spacing = 1;
	int boxCount = 1;

	//ofBackground(74, 88, 150);

	ofPushMatrix();
	
	float t = 0;
	ofVec3f pos(
		ofSignedNoise(t, 0, 0),
		ofSignedNoise(0, t, 0),
		ofSignedNoise(0, 0, t));
	
	float boxSize = 251;
	
	
	ofTranslate(pos);
	ofRotateX(pos.x);
	ofRotateY(pos.y);
	ofRotateZ(pos.z);
	
	texture1.bind();
	ofFill();
	//ofSetColor(255);
	ofDrawBox(0,0,0,boxSize,boxSize, 0);
	texture1.unbind();
	
	//ofNoFill();
	//ofSetColor(ofColor::fromHsb(sinf(t) * 128 + 128, 255, 255));
	//ofDrawBox(boxSize * 1.1f);
	
	ofPopMatrix();

	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch(key){
		case 'F':
		case 'f':
			ofToggleFullscreen();
			break;
		case 'Q':
		case 'q':

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
	if(button == OF_MOUSE_BUTTON_RIGHT)
		cam.setDistance(mouseX+75);
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
