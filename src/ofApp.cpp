#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	ofSetVerticalSync(true);
	
	// this uses depth information for occlusion
	// rather than always drawing things on top of each other
	ofEnableDepthTest();
	
	// this sets the camera's distance from the object
	cam.setDistance(10000);

	//for the cameras
	grabber1.initGrabber(vW,vH);
	grabber2.initGrabber(vW,vH);
		
	
	texture1.allocate(vW,vH,GL_RGB);
	texture2.allocate(vW,vH,GL_RGB);
	ofLogo.loadImage("of.png");

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
	if(!STATIC_IMAGE){
	client1.setup(10);
	client1.addVideoChannel(5004);
	client2.setup(10);
	client2.addVideoChannel(6000);
	}
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

	if(!STATIC_IMAGE){
	client1.play();
	client2.play();
	}
	//server.play();

    ofSetFrameRate(75);
	ofBackground(155);
}


void ofApp::exit(){
}


//--------------------------------------------------------------
void ofApp::update(){


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
	}else{
		texture1.loadData(ofLogo.getPixelsRef());
	//	texture1.loadData(ofLogo.getTextureReference());
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	cam.begin();


	ofSetColor(255);
	//remoteVideo.draw(0,0);

    //calculate the proper cropping location
    cropPositionX = vW-mouseX*2;
    cropPositionY = vH-mouseY*2;
    if(cropPositionX < 0){
        cropPositionX = 0;
    }else if(cropPositionX > vW-cropSizeX){
        cropPositionX = vW-cropSizeX;
    }
    if (cropPositionY < 0){
        cropPositionY = 0;
    }else if(cropPositionY > vH- cropSizeY){
        cropPositionY = vH- cropSizeY;
    }

	//K, first 2 numbers are location on the canvas, next 2 are the crop size, 2 are position out of the image to crop at.
	texture1.drawSubsection(0,0, cropSizeX, cropSizeY, cropPositionX, cropPositionY);
	texture2.drawSubsection(cropSizeX,0, cropSizeX, cropSizeY, cropPositionX, cropPositionY);
	//grabber1.draw(400,300,240,180);
	//grabber2.draw(400,300,240,180);
	//gui.draw();
	cam.end();
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
