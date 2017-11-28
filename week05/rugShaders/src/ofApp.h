#pragma once

#define WEBCAM


#include "ofMain.h"
#include "ofxGui.h"


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

    ofShader shader;
    
    ofImage image;
    ofImage img;
    ofImage clip;
    ofImage imageMask;
    ofVideoPlayer video;
//    ofVideoGrabber camera;
    
    ofPlanePrimitive plane;
    ofSpherePrimitive sphere;
    
    ofMesh mesh;
    ofEasyCam cam;
    
    ofFbo fbo;
    ofFbo maskFbo;
    
    
};
