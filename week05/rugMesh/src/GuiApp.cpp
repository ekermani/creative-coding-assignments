//
//  GuiApp.cpp
//  rugMesh
//
//
//

#include "GuiApp.h"

void GuiApp::setup(){
    
    parameters.setName("parameters");
//    parameters.add(radius.set("radius",50,1,100));
//    parameters.add(color.set("color",100,ofColor(0,0),255));
    gui.setup(parameters);
    ofBackground(0);
//    ofSetVerticalSync(false);
}

void GuiApp::update(){
    
}

void GuiApp::draw(){
    gui.draw();
    
    ofSetColor(50, 226, 34);
    ofDrawBitmapString("RUG LIFE", 10, 20);
    ofDrawBitmapString("fullscreen mode: press F", 10, 40);
    ofDrawBitmapString("Click for more", 10, 60);

    

}
