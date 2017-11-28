#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    clouds.load("clouds.jpg");
    carpet.load("carpet-small.jpg");
    
//    int width = image.getWidth();
//    int height = image.getHeight();
    
    smoothValue = ofVec2f(0,0);
    scale = ofVec2f(129,100);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetRectMode(OF_RECTMODE_CORNER);

    clouds.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    //smoothValue.x = .99*smoothValue.x + .01*mouseX;
    //smoothValue.y =
    smoothValue = .99*smoothValue + .01*ofVec2f(mouseX,mouseY);
    
    
//    float ofMap(float value, float inputMin, float inputMax, float outputMin, float outputMax, bool clamp=false)
    
    //distance of window ofGetWidth
    
    // distance between the center of the image
    float distance = ofDist(ofGetWidth()/2,ofGetHeight()/2,smoothValue.x, smoothValue.y);
    
    float newValue = ofMap(distance, 0, ofGetWidth()/2, .5,2);
                           
    ofSetRectMode(OF_RECTMODE_CENTER);
    carpet.draw(smoothValue,scale.x*newValue,scale.y*newValue);

                           

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
