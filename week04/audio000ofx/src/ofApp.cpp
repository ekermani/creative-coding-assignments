#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup(){
    
    // camera part
    camera.setup(640, 480);
    
    //shader part
    
    shader.load("shader.vert","shader.frag");
    
    //load an image, create mesh/primitive
    water.load("water.jpg");
    water.update();

//    plane.set(800, 800, 50, 50, OF_PRIMITIVE_TRIANGLES);
//    plane.mapTexCoordsFromTexture(water.getTexture());

    
    sphere.setRadius(250);
    sphere.mapTexCoordsFromTexture(water.getTexture());
    
    
    
    // sound audioInput
    
    ofSetVerticalSync(true);
    
//    ofSetCircleResolution(80);
//    ofBackground(54, 54, 54);
    
    soundStream.printDeviceList();
    
    int bufferSize = 256;
    
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    volHistory.assign(400, 0.0);
    
    bufferCounter	= 0;
    drawCounter		= 0;
    smoothedVol     = 0.0;
    scaledVol = 0.0;
    
    // 0 output channels,
    // 2 input channels
    // 44100 samples per second
    // 256 samples per buffer
    // 4 num buffers (latency)
    
    soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
    
        
    // if you want to set the device id to be different than the default
    // auto devices = soundStream.getDeviceList();
    // settings.device = devices[4];
    
    // you can also get devices for an specific api
    // auto devices = soundStream.getDevicesByApi(ofSoundDevice::Api::PULSE);
    // settings.device = devices[0];
    
    // or get the default device for an specific api:
    // settings.api = ofSoundDevice::Api::PULSE;
    
    // or by name
//    auto devices = soundStream.getMatchingDevices("default");
//    if(!devices.empty()){
//        settings.setInDevice(devices[0]);
//    }
    
//    decayRate = 0.05;
//    minimumThreshold = 0.1;
//    threshold = minimumThreshold;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    camera.update();
    
    // how fast learns background
    int learningTime = 30;
    
    // threshold image value
    int thresholdValue = 10;
    
    if(camera.isFrameNew()) {
        background.setLearningTime(learningTime);
        background.setThresholdValue(thresholdValue);
        background.update(camera, thresholded);
        
        thresholded.update();
    }
    
    //lets scale the vol up to a 0-1 range
    scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
    
    //lets record the volume into an array
    volHistory.push_back( scaledVol );
    
    //if we are bigger the the size we want to record - lets drop the oldest value
    if( volHistory.size() >= 400 ){
        volHistory.erase(volHistory.begin(), volHistory.begin()+1);
    }
    
}




//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetBackgroundColor(0);
    
//    if ( thresholded.isAllocated()) {
//        thresholded.draw(640,0);
//    }
    
    ofEnableDepthTest();
    water.bind();
//    camera.draw();
    camera.bind();

    
    cam.begin();
    shader.begin();
        shader.setUniform1f("time", smoothedVol);
//        plane.drawWireframe();
        sphere.drawWireframe();
    shader.end();
    cam.end();
    
    ofDisableDepthTest();
    
    
//    ofSetColor(225);
//    ofDrawBitmapString("AUDIO INPUT EXAMPLE", 32, 32);
//    ofDrawBitmapString("press 's' to unpause the audio\n'e' to pause the audio", 31, 92);
//    
//    ofNoFill();
//    
//    // draw the left channel:
//    ofPushStyle();
//    ofPushMatrix();
//    ofTranslate(32, 170, 0);
//    
//    ofSetColor(225);
//    ofDrawBitmapString("Left Channel", 4, 18);
//    
//    ofSetLineWidth(1);
//    ofDrawRectangle(0, 0, 512, 200);
//    
//    ofSetColor(245, 58, 135);
//    ofSetLineWidth(3);
//    
//    ofBeginShape();
//    for (unsigned int i = 0; i < left.size(); i++){
//        ofVertex(i*2, 100 -left[i]*180.0f);
//    }
//    ofEndShape(false);
//    
//    ofPopMatrix();
//    ofPopStyle();
//    
//    // draw the right channel:
//    ofPushStyle();
//    ofPushMatrix();
//    ofTranslate(32, 370, 0);
//    
//    ofSetColor(225);
//    ofDrawBitmapString("Right Channel", 4, 18);
//    
//    ofSetLineWidth(1);
//    ofDrawRectangle(0, 0, 512, 200);
//    
//    ofSetColor(245, 58, 135);
//    ofSetLineWidth(3);
//    
//    ofBeginShape();
//    for (unsigned int i = 0; i < right.size(); i++){
//        ofVertex(i*2, 100 -right[i]*180.0f);
//    }
//    ofEndShape(false);
//    
//    ofPopMatrix();
//    ofPopStyle();
//    
//    // draw the average volume:
//    ofPushStyle();
//    ofPushMatrix();
//    ofTranslate(565, 170, 0);
//    
//    ofSetColor(225);
//    ofDrawBitmapString("Scaled average vol (0-100): " + ofToString(scaledVol * 100.0, 0), 4, 18);
//    ofDrawRectangle(0, 0, 400, 400);
//    
//    ofSetColor(245, 58, 135);
//    ofFill();
//    ofDrawCircle(200, 200, scaledVol * 190.0f);
//    
//    //lets draw the volume history as a graph
//    ofBeginShape();
//    for (unsigned int i = 0; i < volHistory.size(); i++){
//        if( i == 0 ) ofVertex(i, 400);
//        
//        ofVertex(i, 400 - volHistory[i] * 70);
//        
//        if( i == volHistory.size() -1 ) ofVertex(i, 400);
//    }
//    ofEndShape(false);
//    
//    ofPopMatrix();
//    ofPopStyle();
//    
//    drawCounter++;
//    
//    ofSetColor(225);
//    string reportString = "buffers received: "+ofToString(bufferCounter)+"\ndraw routines called: "+ofToString(drawCounter)+"\nticks: " + ofToString(soundStream.getTickCount());
//    ofDrawBitmapString(reportString, 32, 589);


}
//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    float curVol = 0.0;
//    float rms = 0.0;
    
    
    // samples are "interleaved"
    int numCounted = 0;
    
    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (int i = 0; i < bufferSize; i++){
        left[i]		= input[i*2]*0.5;
        right[i]	= input[i*2+1]*0.5;
        
        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        numCounted+=2;
    }
    
//    for (int i = 0; i < bufferSize; i++){
//        float leftSample = input[i * 2] * 0.5;
//        float rightSample = input[i * 2 + 1] * 0.5;
//        
//        rms += leftSample * leftSample;
//        rms += rightSample * rightSample;
//        numCounted += 2;
//        
//        rms /= (float)numCounted;
//        rms = sqrt(rms);
//        // rms is now calculated
//        
//    }
//
    //this is how we get the mean of rms :)
    curVol /= (float)numCounted;
    
    // this is how we get the root of rms :)
    curVol = sqrt( curVol );
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
    
    bufferCounter++;
    
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 's') {
        
    }
    
//    if( key == 's' ){
//        soundStream.start();
//    }
//    
//    if( key == 'e' ){
//        soundStream.stop();
//    }
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
