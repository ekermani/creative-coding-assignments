#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    //------LINES---------//
//    ofBackground(255,255,255);

    isDrawing = false;
    
    smoothValue = ofVec2f(0,0);

    
    //------KINECT---------//
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    // enable depth->video image calibration
    kinect.setRegistration(true);
    
    kinect.init();
    //kinect.init(true); // shows infrared instead of RGB video image
    //kinect.init(false, false); // disable video image (faster fps)
    
    kinect.open();        // opens first available kinect
    
    // print the intrinsic IR sensor values
    if(kinect.isConnected()) {
        ofLogNotice() << "sensor-emitter dist: " << kinect.getSensorEmitterDistance() << "cm";
        ofLogNotice() << "sensor-camera dist:  " << kinect.getSensorCameraDistance() << "cm";
        ofLogNotice() << "zero plane pixel size: " << kinect.getZeroPlanePixelSize() << "mm";
        ofLogNotice() << "zero plane dist: " << kinect.getZeroPlaneDistance() << "mm";
    }
    
    colorImg.allocate(kinect.width, kinect.height);
    grayImage.allocate(kinect.width, kinect.height);
    grayThreshNear.allocate(kinect.width, kinect.height);
    grayThreshFar.allocate(kinect.width, kinect.height);
    
    nearThreshold = 255;
    farThreshold = 240;
    bThreshWithOpenCV = true;
    
    ofSetFrameRate(60);
    
    // zero the tilt on startup
    angle = 0;
    kinect.setCameraTiltAngle(angle);
    
}

//--------------------------------------------------------------
void ofApp::update(){

    //------KINECT---------//
    ofBackground(255, 255, 255);
    
    kinect.update();
    
    // there is a new frame and we are connected
    if(kinect.isFrameNew()) {
        
        // load grayscale depth image from the kinect source
        grayImage.setFromPixels(kinect.getDepthPixels());
        
        // we do two thresholds - one for the far plane and one for the near plane
        // we then do a cvAnd to get the pixels which are a union of the two thresholds
        if(bThreshWithOpenCV) {
            grayThreshNear = grayImage;
            grayThreshFar = grayImage;
            grayThreshNear.threshold(nearThreshold, true);
            grayThreshFar.threshold(farThreshold);
            cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
        } else {
            
            // or we do it ourselves - show people how they can work with the pixels
            ofPixels & pix = grayImage.getPixels();
            int numPixels = pix.size();
            for(int i = 0; i < numPixels; i++) {
                if(pix[i] < nearThreshold && pix[i] > farThreshold) {
                    pix[i] = 255;
                } else {
                    pix[i] = 0;
                }
            }
        }
        
        // update the cv images
        grayImage.flagImageChanged();
        
        // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
        // also, find holes is set to true so we will get interior contours as well....
        contourFinder.findContours(grayImage, 10, (kinect.width*kinect.height)/2, 20, false);
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    kinect.draw(420, 10, 400, 300);  // !! make larger, to fill screen
    contourFinder.draw(10, 10, 400, 300);  // !! remove after testing
    
    for (auto line : lines) {
        
        // connect the lines, where line begins/ends
        ofDrawLine(line.a, line.b);
    }
    
    ofSetColor(255, 255, 255);
    
    // check if have at least one countour
    if (contourFinder.blobs.size() > 0) {
        
        // might need to scale from camera size to size of screen
        // width/camera width to scale it up
        float scaleH = ofGetHeight() / 480.0;
        float scaleW = ofGetWidth() / 640.0;  // kinect 640?
        
        // find contour center of largest blob tracked
        float cx = contourFinder.blobs[0].boundingRect.getCenter().x;
        float cy = contourFinder.blobs[0].boundingRect.getCenter().y;
        
        // add points here
        
        // scale up to screen size so animation is full screen
        cx *= scaleW;
        cy *= scaleH;
        
        smoothValue.x = .9*smoothValue.x + .1*cx;
        smoothValue.y = .9*smoothValue.y + .1*cy;


        
        // now use cx and cy for lines
            if(isDrawing){
                ofPoint pt;
                //pt.set(cx,cy);
                pt.set(smoothValue.x,smoothValue.y);
//                pt.set(mouseX,mouseY);
                line.addVertex(pt);
        
                // takes current position of mouse ofPoint mouse and confront with previous position
                for (auto point : drawnPoints) {
                  // ofPoint mouse;
                    ofPoint move;
                  // mouse.set(mouseX,mouseY);
                    move.set(smoothValue.x,smoothValue.y);

                    float dist = (move - point).length();

                    // if distance between current and previous positions less than 30 pixel
                    // then create Line lineTemp that connects position of mouse with point in history vector "drawnPoints"
                    if (dist < 30) {
                        Line lineTemp;
                        lineTemp.a = move;
                        lineTemp.b = point;
                        lines.push_back(lineTemp);
                    }
                }
                drawnPoints.push_back(ofPoint(smoothValue.x,smoothValue.y));
                    // connect points a and b
                
            }
    }

    
    
//------LINES---------//

    ofSetColor(30,30,30,30);
    line.draw();
    ofEnableAlphaBlending();
    
        // each time drag mouse, saving position of mouse in drawnPoints
        // (history of all movements of mouse on screen)
       // drawnPoints.push_back(ofPoint(mouseX,mouseY));

//-----KINECT-----//
    
//        kinect.drawDepth(10, 10, 400, 300);
//        grayImage.draw(10, 320, 400, 300);
    
    ofSetColor(50,50,50);
    stringstream reportStream;
    
    reportStream
    << "using opencv threshold = " << bThreshWithOpenCV <<" (press spacebar)" << endl
    << "set near threshold " << nearThreshold << " (press: + -)" << endl
    << "set far threshold " << farThreshold << " (press: < >) num blobs found " << contourFinder.nBlobs;
    
    ofDrawBitmapString(reportStream.str(), 20, 500);
    
}
    
//--------------------------------------------------------------
void ofApp::exit() {
    kinect.setCameraTiltAngle(0); // zero the tilt on exit
    kinect.close();

}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch (key) {
        
        case 'd':
            isDrawing = !isDrawing;
//            break;
            
        case ' ':
            bThreshWithOpenCV = !bThreshWithOpenCV;
            break;
            
        case '>':
        case '.':
            farThreshold ++;
            if (farThreshold > 255) farThreshold = 255;
            break;
            
        case '<':
        case ',':
            farThreshold --;
            if (farThreshold < 0) farThreshold = 0;
            break;
            
        case '+':
        case '=':
            nearThreshold ++;
            if (nearThreshold > 255) nearThreshold = 255;
            break;
        
        case '-':
            nearThreshold --;
            if (nearThreshold < 0) nearThreshold = 0;
            break;
        
        case 'w':
            kinect.enableDepthNearValueWhite(!kinect.isDepthNearValueWhite());
            break;
       
        case 'o':
            kinect.setCameraTiltAngle(angle);   // go back to prev tilt
            kinect.open();
            break;
        
        case 'c':
            kinect.setCameraTiltAngle(0);       // zero the tilt
            kinect.close();
            break;
//        case 's'://s to toggle saving data
//            saveData = !saveData;
//            break;
            
        case OF_KEY_UP:
            angle++;
            if(angle>30) angle=30;
            kinect.setCameraTiltAngle(angle);
            break;
            
        case OF_KEY_DOWN:
            angle--;
            if(angle<-30) angle=-30;
            kinect.setCameraTiltAngle(angle);
            break;
            
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
//    isDrawing = true;

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
