#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"

class Line {
public:
    ofPoint a;
    ofPoint b;
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
    
    ofNode baseNode;
    ofNode childNode;
    ofNode grandChildNode;
    ofPolyline line;
    vector < ofPoint > drawnPoints;
    vector < Line> lines;

    ofEasyCam cam;

    ofVideoGrabber camera;
    ofImage thresholded;

    ofPixels previous;
    ofImage diff;

//    ofxCv::RunningBackground background;

    cv::Scalar diffMean;
    
    bool isDrawing;
    
};
