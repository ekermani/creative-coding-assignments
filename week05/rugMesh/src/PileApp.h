//
//  PileApp.hpp
//  rugMesh
//

#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class PileApp: public ofBaseApp {

public:
    void setup();
    void update();
    void draw();
    void drawPile();
    void drawRandomInWindow();
    
    ofImage rug;

};
