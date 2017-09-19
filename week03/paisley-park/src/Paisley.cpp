//
//  Paisley.cpp
//  paisley-park
//
//
//

#include "Paisley.h"

void PaisleyP::setup() {
    
    pos = ofPoint( ofRandom(1024), ofRandom(768) );
    vel = ofVec2f( ofRandom(-5,5), ofRandom(-5,5) );
    
    //    rot = ofVec2f( );

    
}

void PaisleyP::update() {
    
    pos += vel;
    vel *= .99;
    
    ofSetBackgroundAuto(false);
    ofBackground(randomColor);


}

void PaisleyP::draw() {
    
//    setStrokeColor(0);
//    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetColor(randomColor);
//    ofRotateX(45);
//    ofRectangle( pos, 50, 50);
    
    ofDrawEllipse( pos, ofRandom(30, 50), ofRandom(100, 500) );
    ofNoFill();

    
    
//    ofBeginShape();
//        ofDrawCircle( pos, 30);
//        ofVertex(400,135);
//        ofVertex(215,135);
//        ofVertex(365,25);
//        ofVertex(305,200);
//        ofVertex(250,25);
//    ofEndShape();
    
}
