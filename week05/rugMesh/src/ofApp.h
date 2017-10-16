#pragma once

#include "ofMain.h"
#include "GuiApp.h"
#include "VideoApp.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"

//enum windowSwitch {
//    IDLE = 0,
//    VIDEO,
//    GUI
//    
//};


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void drawGui( ofEventArgs & args);
        void drawVideo( ofEventArgs & args);
//        void drawRandomInWindow( ofEventArgs & args);
        void drawSeq( ofEventArgs & args);
        void drawPile( ofEventArgs & args);

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
    
        std::vector<shared_ptr<ofAppBaseWindow> > windows;
    
//        ofMesh mesh;
    
    // audio
    ofSoundPlayer music;
    
    void audioIn(float * input, int bufferSize, int nChannels);
    
    vector <float> left;
    vector <float> right;
    vector <float> volHistory;
    
    int bufferCounter;
    int drawCounter;
    
    float smoothedVol;
    float scaledVol;
    
    ofSoundStream soundStream;
    
    ofShader shader;
    ofImage rug;
    ofPlanePrimitive plane;
    ofEasyCam easyCam;
    VideoApp vidapp;
    GuiApp guiapp;

    
//    ofxCv::RunningBackground background;
};

