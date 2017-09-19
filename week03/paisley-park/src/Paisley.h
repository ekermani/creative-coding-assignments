//
//  Paisley.hpp
//  paisley-park
//
//
//

//#ifndef Paisley_h
//#define Paisley_h
//
//#include <stdio.h>
//
//#endif /* Paisley_hpp */

#pragma once

#include "ofMain.h"

class PaisleyP {
    
    public:
    
        void setup();
        void update();
        void draw();
    
        ofPoint pos;
        ofVec2f vel;
//        ofVec2f rot;
    
        float randomColor = ofRandom(5,255);

};
