//
//  VideoApp.cpp
//  rugMesh
//
// based on example for ofxImageSequence addon; updated due to deprecated code


#include "VideoApp.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"

using namespace ofxCv;
using namespace cv;

void VideoApp::setup(){
    
	//prefix is frame, file type is png, from frame 1 to 11, 2 digits in the number
    sequence.loadSequence("frame", "png", 1, 3, 2);
    sequence.preloadAllFrames();	//this way there is no stutter when loading frames
    sequence.setFrameRate(1); //set to ten frames per second for Muybridge's horse.
    
    playing = true; //controls if playing automatically, or controlled by the mouse
    
}

void VideoApp::update(){
    
}

void VideoApp::draw(){

    
    sequence.getTextureForTime(ofGetElapsedTimef()).draw(0,0);
//sequence.getTextureForTime(<#float time#>)
    
//    if(playing){
//        //get the frame based on the current time and draw it
//        sequence.getFrame(ofGetElapsedTimef())->draw(0,0);
//    }
//    else {
//        //get the sequence frame that maps to the mouseX position
//        float percent = ofMap(mouseX, 0, ofGetWidth(), 0, 1.0, true);
//        
//        //draw it.
//        sequence.getFrameAtPercent(percent)->draw(0, 0);


    }

