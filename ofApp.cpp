/************************************************************
************************************************************/
#include "ofApp.h"

/************************************************************
************************************************************/

//--------------------------------------------------------------
void ofApp::setup(){
	/********************
	********************/
	ofSetBackgroundAuto(true);
	
	ofSetWindowTitle("Fbo anti-aliasing");
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofSetWindowShape(WIDTH, HEIGHT);
	ofSetEscapeQuitsApp(false);
	
	ofSetCircleResolution(200);
	
	id_whichSurfaceToDraw = SURFACE_SCREEN;
	
	/********************
	********************/
	mainOutputSyphonServer.setName("Screen Output"); // server name
	fbo_TextureSyphonServer[0].setName("fbo_0 Output");
	fbo_TextureSyphonServer[1].setName("fbo_1 Output");

	/*
	mClient.setup();
	//using Syphon app Simple Server, found at http://syphon.v002.info/
	mClient.set("","Simple Server"); // void set(string _serverName, string _appName);
	*/
	
	fbo[0].allocate(ofGetWidth(), ofGetHeight(), GL_RGBA, 0);
	fbo[1].allocate(ofGetWidth(), ofGetHeight(), GL_RGBA, 5);
	
	font[0].load("RictyDiminished-Regular.ttf", 50, true, true, true);
	font[1].load("RictyDiminished-Bold", 50, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
	/********************
	********************/
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	ofEnableSmoothing();
	// ofDisableSmoothing();
	
	ofEnableAlphaBlending();
	// ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofEnableBlendMode(OF_BLENDMODE_ADD);

	/********************
	********************/
	for(int i = 0; i < 2; i++){
		fbo[i].begin();
			ofClear(0);
			drawContents();
		fbo[i].end();
	}
	
	/********************
	********************/
	ofClear(0);
	ofSetColor(255, 255, 255, 255);
	switch(id_whichSurfaceToDraw){
		case 0:
			drawContents();
			break;
		case 1:
			fbo[0].draw(0, 0);
			break;
		case 2:
			fbo[1].draw(0, 0);
			break;
	}
	
	/********************
	********************/
	/* publish */
	mainOutputSyphonServer.publishScreen();
	
	for(int i = 0; i < 2; i++){
		ofTexture tex = fbo[i].getTextureReference();
		fbo_TextureSyphonServer[i].publishTexture(&tex);
	}
}

/******************************
******************************/
void ofApp::drawContents()
{
	double LineWidth = 3.0;
	
	ofSetColor(255, 255, 255, 255);
	ofNoFill();
	ofSetLineWidth(LineWidth);
	ofDrawTriangle(200, 100, 100, 300, 300, 300);
	ofDrawCircle(200, 700, 150);
	
	ofSetColor(255, 255, 255, 240);
	ofNoFill();
	ofSetLineWidth(LineWidth);
	ofDrawLine(400, 300, 700, 100);
	
	ofSetColor(255, 255, 255, 240);
	ofFill();
	ofSetLineWidth(LineWidth);
	ofDrawTriangle(800, 100, 700, 300, 900, 300);
	ofDrawCircle(800, 700, 150);
	
	ofSetColor(255, 255, 255, 240);
	font[0].drawStringAsShapes("0123456789", 300, 400);
	font[0].drawStringAsShapes("NOBUHIRO SAIJO", 330, 420);
	font[1].drawStringAsShapes("0123456789", 300, 500);
	font[1].drawStringAsShapes("NOBUHIRO SAIJO", 330, 520);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key){
		case '0':
		case '1':
		case '2':
			if(key - '0' < NUM_SURFACE_ID){
				id_whichSurfaceToDraw = SURFACE_TO_DRAW(key - '0');
				printf("id = %d\n", id_whichSurfaceToDraw);
			}
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
