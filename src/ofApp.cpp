#include "ofApp.h"

//-------------------------------------------------------------


void ofApp::setup(){

	vW  = 1920;
	vH  = 1080;
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

	//grabber1.initGrabber(vW,vH);
	//grabber2.initGrabber(vW,vH);
#if VIDEO
	texture1.allocate(vW,vH,GL_RGB);
	texture2.allocate(vW,vH,GL_RGB);

	client1.setup(10);
	client1.addVideoChannel(5000);
	client2.setup(10);
	client2.addVideoChannel(5001);
	client1.play();
	client2.play();

#endif

#if STATIC_IMAGE //so Image
	ofLogo.setUseTexture(true);
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

//createMeshWithTexture(texture1);
//drawMesh();

	ratio = 3 / (double) 4;
	fov = 200;
	precision = 2000;
	radius = 5000;

	// generate segment
	this->createSegmentedMesh(ofVec3f(0,0,0), radius, precision, longMin, longMax, latMin, latMax);



}


void ofApp::exit(){

}


//--------------------------------------------------------------
void ofApp::update(){

#if VIDEO

	/* code */

	//grabber1.update();
	//grabber2.update();
	//if(grabber.isFrameNew()){
	//	server.newFrame(grabber.getPixelsRef());
	//}

	client1.update();
	client2.update();
	
	if(!STATIC_IMAGE){
		if(client1.isFrameNewVideo()){
			texture1.loadData(client1.getPixelsVideo());
			//temp
			texture2.loadData(client1.getPixelsVideo());
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
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	


    ofPushMatrix();
	ofRotate(90, 0, 0, -10);
    ofDrawGridPlane(100.0f, 2.0f, false );
	ofPopMatrix();


	ofPushMatrix();
	

	ofVec3f pos(
		0,
		0,
		0);
	
	//float planeSize = 9000;
	
	
	ofTranslate(pos);
	ofRotateX(pos.x);
	ofRotateY(pos.y);
	ofRotateZ(pos.z);
	
	ofEnableDepthTest();

	if(side == 0){ // left eye
		ofLogo.bind();
	//ofFill();
		mesh.draw();
		//ofDrawSphere(0,0,1080);
		ofLogo.unbind();

		//ofSetColor(255);
		//ofDrawSphere(0,0,0,planeSize);
		
		
	}else{ //right eye

	texture1.bind();
	ofFill();
	//ofSetColor(255);
	ofDrawBox(0,0,0,108,100, 0);
	//ofDrawSphere(0,0,1080);
	texture1.unbind();
		
	}	
	glDisable(GL_CULL_FACE);
	ofDisableAlphaBlending();

	ofDisableDepthTest();	

	
	ofPopMatrix();
}
/*
void ofApp::drawSceneImage(){ //not used, aka, delete me!

	
	float movementSpeed = .1;
	float maxplaneSize = 100;
	float spacing = 1;
	int boxCount = 1;

	//ofBackground(74, 88, 150);

	ofPushMatrix();
	
	float t = 0;
	ofVec3f pos(
		ofSignedNoise(t, 0, 0),
		ofSignedNoise(0, t, 0),
		ofSignedNoise(0, 0, t));
	
	float planeSize = 251;
	
	
	ofTranslate(pos);
	ofRotateX(pos.x);
	ofRotateY(pos.y);
	ofRotateZ(pos.z);
	
	texture1.bind();
	ofFill();
	//ofSetColor(255);
	//ofDrawBox(0,0,0,planeSize,planeSize, 0);
	ofDrawSphere(100,100,100);
	texture1.unbind();
	
	

	//ofNoFill();
	//ofSetColor(ofColor::fromHsb(sinf(t) * 128 + 128, 255, 255));
	//ofDrawBox(planeSize * 1.1f);
	
	ofPopMatrix();

	
}*/
/*
void ofApp::createMeshWithTexture(ofTexture& texture){
	
	//ofSpherePrimitive p = ofSpherePrimitive(100.0,100);
	ofBoxPrimitive p = ofBoxPrimitive(1920,1080,0,100,100, 0);
	
	mesh = p.getMesh();
	
	for(int i = 0; i < mesh.getNumVertices(); i++){
		ofVec2f texCoord = mesh.getTexCoord(i);
		texCoord.x *= texture.getWidth();
		texCoord.y  = (1.0 - texCoord.y) * texture.getHeight();
		mesh.setTexCoord(i, texCoord);
	}
	ofLog(OF_LOG_VERBOSE, "aaaaaaaaaaaaaaaaaaaaaa" + ofToString(mesh.getNumVertices()));
	
}*/

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch(key){
		case 'F':
		case 'f':
			ofToggleFullscreen();
			break;
		case 'Q':
		case 'q':
			oculusRift.dismissSafetyWarning();
			break;
	}
}

void ofApp::createSegmentedMesh(const ofVec3f& center,
                                double radius,
                                int precision,
                                double theta1, double theta2,
                                double phi1, double phi2)
{
    /*
     Create a sphere centered at c, with radius r, and precision n
     Draw a point for zero radius spheres
     Use CCW facet ordering
     Partial spheres can be created using theta1->theta2, phi1->phi2
     in radians 0 < theta < 2pi, -pi/2 < phi < pi/2
     */
    int i,j;
    double t1,t2,t3;
    ofVec3f e,p;
    
    mesh.clear();

	/* Handle special cases */
    if (radius < 0)
        radius = -radius;
    if (precision < 0)
        precision = -precision;
    if (precision < 4 || radius <= 0) {
        mesh.addVertex(center);
        return;
    }
    
    for (j=0;j<precision/2;j++) {
        t1 = phi1 + j * (phi2 - phi1) / (precision/2);
        t2 = phi1 + (j + 1) * (phi2 - phi1) / (precision/2);

        mesh.setMode(OF_PRIMITIVE_POINTS);
        
        for (i=0;i<=precision;i++) {
            t3 = theta1 + i * (theta2 - theta1) / precision;
            
            e.x = cos(t1) * cos(t3);
            e.y = sin(t1);
            e.z = cos(t1) * sin(t3);
            p.x = center.x + radius * e.x;
            p.y = center.y + radius * e.y;
            p.z = center.z + radius * e.z;
            mesh.addNormal(e);
            mesh.addTexCoord(ofVec2f( (i/(double)precision) * ofLogo.getWidth(),
                                      ofLogo.getHeight() - (2*j/(double)precision) * ofLogo.getHeight()));
            mesh.addVertex(p);
            
            e.x = cos(t2) * cos(t3);
            e.y = sin(t2);
            e.z = cos(t2) * sin(t3);
            p.x = center.x + radius * e.x;
            p.y = center.y + radius * e.y;
            p.z = center.z + radius * e.z;
            mesh.addNormal(e);
            mesh.addTexCoord(ofVec2f( (i/(double)precision) * ofLogo.getWidth(),
                                      ofLogo.getHeight() - (2*(j+1)/(double)precision) * ofLogo.getHeight()));
            mesh.addVertex(p);
		}
    }
}


/*
void ofApp::drawMesh(){

    mesh.setMode(OF_PRIMITIVE_POINTS);

    float intensityThreshold = 0.0;
    int w = ofLogo.getWidth();
    int h = ofLogo.getHeight();
    for (int x=0; x<w; ++x) {
        for (int y=0; y<h; ++y) {
            ofColor c = ofLogo.getColor(x, y);
            float intensity = c.getLightness();
            if (intensity >= intensityThreshold) {
                ofVec3f pos(x, y, 0);
                mesh.addVertex(pos);
                mesh.addTexCoord(pos);
                mesh.addColor(ofFloatColor(100,100,100));
            }
        }
    }

     for (int y = 0; y<h-1; y++){
                for (int x=0; x<w-1; x++){
                        mesh.addIndex(x+y*w);                           // 0
                        mesh.addIndex((x+1)+y*w);                       // 1
                        mesh.addIndex(x+(y+1)*w);                       // 10

                        mesh.addIndex((x+1)+y*w);                       // 1
                        mesh.addIndex((x+1)+(y+1)*w);           // 11
                        mesh.addIndex(x+(y+1)*w);                       // 10
                }
        }

}*/

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
