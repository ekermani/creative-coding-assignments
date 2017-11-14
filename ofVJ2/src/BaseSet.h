//
//  VJIdleSet.h
//  ofVJSet
//
//  Created by csugrue on 11/9/17.
//

#pragma once

#include "ofMain.h"

class BaseSet{
    
public:
    
    virtual void setup(){ title = ""; };
    virtual void update(){};
    virtual void draw(){};
    virtual void pause(){};
    virtual void start(){};
    
    virtual void mouseMoved(ofMouseEventArgs& mouse){};
    virtual void keyPressed(ofKeyEventArgs & key){};
    
    int mouseX, mouseY;
    bool isPlaying;
    string title;
    
};
