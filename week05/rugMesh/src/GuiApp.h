//
//  GuiApp.hpp
//  rugMesh
//
//

#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class GuiApp: public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void drawGui();
    
    ofParameterGroup parameters;
    ofParameter<float> radius;
    ofParameter<ofColor> color;
    ofxPanel gui;
};
