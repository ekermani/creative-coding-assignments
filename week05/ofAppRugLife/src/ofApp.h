#pragma once

#include "ofMain.h"
#include "ofx3DFont.h"
#include "ofxGui.h"
#include "ofxImageSequence.h"


//STATES
enum gameState {
    //creating variables
    //clean way to manage dif states of game
    START = 0,
    SCENE_1,
    SCENE_2,
};


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    wstring show;
    string strAlign;
    string strDirection;
    bool renderingMode;
    bool bRotation;
    int align;
    
    ofx3DFont face;
    ofx3DFont faceNavi3d;
    ofLight light;
    
//    ofxFloatSlider rotate;
//    ofxFloatSlider scale;
    ofParameterGroup parameters;
    ofParameter<ofColor> color;
    ofParameter<float> scale;
    ofParameter<float> rotate;
    ofxPanel gui;
    
    //Scene states
    gameState currentState;

    ofxImageSequence sequence;
    bool playing;
    
    ofShader shader;
    ofEasyCam easyCam;
    ofImage rug;
    ofImage texture;
    ofPlanePrimitive plane;

		
};
