#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    //------LINES---------//
    ofBackground(255,255,255);
    
    ofSetVerticalSync(true);
    //    camera.setup(1024,576);
    //    camera.setup(320,240);
    
    // imitate() will set up previous and diff
    // so they have the same size and type as cam
//    imitate(previous, camera);
//    imitate(diff, camera);
    
    isDrawing = false;

}

//--------------------------------------------------------------
void ofApp::update(){



}

//--------------------------------------------------------------
void ofApp::draw(){
    //------LINES---------//

    line.draw();
    ofEnableAlphaBlending();
    ofSetColor(30,30,30,30);
    
    // connect points a and b
    for (auto line : lines) {
        ofDrawLine(line.a, line.b);
    }
    
    ofPushMatrix();
    
    
    //    ofEnableDepthTest();
    camera.draw(0,0);
    
    diff.draw(320,0);
    
    //    if(thresholded.isAllocated()) {
    //        thresholded.draw(640,0);
    //
    //    }
    
    //    ofDisableDepthTest();
    
    ofPopMatrix();
    
    // use the [] operator to get elements from a Scalar
    float diffRed = diffMean[0];
    float diffGreen = diffMean[1];
    float diffBlue = diffMean[2];
    
    //    ofSetColor(255, 0, 0);
    //    ofDrawRectangle(0, 0, diffRed, 10);
    //    ofSetColor(0, 255, 0);
    //    ofDrawRectangle(0, 15, diffGreen, 10);
    //    ofSetColor(0, 0, 255);
    //    ofDrawRectangle(0, 30, diffBlue, 10);
    
    if(isDrawing){
        ofPoint pt;
        pt.set(mouseX,mouseY);
        line.addVertex(pt);
        
        // takes current position of mouse ofPoint mouse and confront with previous position
        // if distance between current and previous positions less than 30 pixel
        // then create Line lineTemp that connects position of mouse with point in history vector drawnPoints
        for (auto point : drawnPoints) {
            ofPoint mouse;
            mouse.set(mouseX,mouseY);
            float dist = (mouse - point).length();
            
            if (dist < 30) {
                Line lineTemp;
                lineTemp.a = mouse;
                lineTemp.b = point;
                lines.push_back(lineTemp);
            }
            
            // points first start at larger distance then smaller
            if (dist < 5) {
                Line lineTemp;
                lineTemp.b = mouse;
                lineTemp.a = point;
                lines.push_back(lineTemp);
            }
            
            
        }
        // each time drag mouse, saving position of mouse in drawnPoints
        // (history of all movements of mouse on screen)
        drawnPoints.push_back(ofPoint(mouseX,mouseY));
    }

}
//--------------------------------------------------------------
//void ofApp::drawPointCloud() {
//}
//--------------------------------------------------------------
//void ofApp::exit() {



//}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    isDrawing = true;


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
