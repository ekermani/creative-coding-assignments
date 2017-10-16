#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"

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
    
        // audio
        void audioIn(float * input, int bufferSize, int nChannels);
    
        vector <float> left;
        vector <float> right;
        vector <float> volHistory;
    
        int bufferCounter;
        int drawCounter;
    
        float smoothedVol;
        float scaledVol;
    
        ofSoundStream soundStream;
    
    // modified from audioInputExample
    //        float rms = 0.0;
    //        int numCounted = 0;
    //
    //        // for beat detection
    //        float threshold;
    //        float minimumThreshold;
    //        float decayRate;
    
    
        // shader
        ofShader shader;
        ofImage water;
//        ofPlanePrimitive plane;
        ofSpherePrimitive sphere;
        ofEasyCam cam;
    
        // camera
        ofVideoGrabber camera;
        ofImage thresholded;
    
        ofxCv::RunningBackground background;
    
};
