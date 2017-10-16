//
//  PileApp.cpp
//  rugMesh
//
//
//

#include "PileApp.h"


void PileApp::setup(){
    
    rug.load("rug.jpg");

}

void PileApp::update(){

}

void PileApp::draw() {
    
    rug.draw(0,0);
    rug.resize(175, 50);
    
}

