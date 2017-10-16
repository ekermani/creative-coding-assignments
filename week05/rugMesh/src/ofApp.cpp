#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    
//    ofBackground(255);
//    ofSetCircleResolution(200);
    
    ofSetBackgroundColor(192, 6, 50);

    
    shader.load("shader.vert","shader.frag");

    
    rug.load("rug.jpg");
    rug.update();
    
    // create bool variable for windows to be visible
    bool window = false;
    


    plane.set(400, 400, 50, 50, OF_PRIMITIVE_TRIANGLES);
    plane.mapTexCoordsFromTexture(rug.getTexture());
    
    
//    music.load("Marzeyeh.m4a");

    ofSetVerticalSync(true);
    
    int bufferSize = 256;
    
    for(int i =0; i < 8; i++){
        
        float px = 200;
        float py = 800-windows.size()*75;
        if(py < 0) py = 0;
        
        ofGLFWWindowSettings settings;
        settings.width = 175;
        settings.height = 75;
        settings.setPosition(ofVec2f(px, py));
        settings.resizable = false;
        settings.visible = false;
        windows.push_back( ofCreateWindow(settings) );
        windows.back()->setVerticalSync(false);
        
        if(windows.size() > 1) {
            ofAddListener(windows.back()->events().draw, this,&ofApp::drawPile);
            
        } else if (windows.size() == 8) {
            ofAddListener(windows.back()->events().draw, this,&ofApp::drawSeq);
            
        }
    }
//
//    left.assign(bufferSize, 0.0);
//    right.assign(bufferSize, 0.0);
//    volHistory.assign(400, 0.0);
//    
//    bufferCounter	= 0;
//    drawCounter		= 0;
//    smoothedVol     = 0.0;
//    scaledVol = 0.0;
//    
//    soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
//
//
//    mesh.setMode(OF_PRIMITIVE_POINTS);
//    mesh.setMode(OF_PRIMITIVE_LINES);
//    mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
//    mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
//    
//    mesh.enableColors();
//    mesh.enableIndices();
//
//    
//    ofVec3f top(100.0, 50.0, 0.0);
//    ofVec3f left(50.0, 150.0, 0.0);
//    ofVec3f right(150.0, 150.0, 0.0);
//    
//    mesh.addVertex(top);
//    mesh.addColor(ofFloatColor(1.0, 0.0, 0.0));
//    
//    mesh.addVertex(left);
//    mesh.addColor(ofFloatColor(0.0, 1.0, 0.0));
//    
//    mesh.addVertex(right);
//    mesh.addColor(ofFloatColor(1.0, 1.0, 0.0));
//    
//    mesh.addIndex(0);
//    mesh.addIndex(1);
//    mesh.addIndex(1);
//    mesh.addIndex(2);
//    mesh.addIndex(2);
//    mesh.addIndex(0);
//    
//    float intensityThreshold = 150.0;
//    int w = rug.getWidth();
//    int h = rug.getHeight();
//    for (int x=0; x<w; ++x) {
//        for (int y=0; y<h; ++y) {
//            ofColor c = rug.getColor(x, y);
//            float intensity = c.getLightness();
//            if (intensity >= intensityThreshold) {
//                ofVec3f pos(x, y, 0.0);
//                mesh.addVertex(pos);
//                // When addColor(...), the mesh will automatically convert
//                // the ofColor to an ofFloatColor
//                mesh.addColor(c);
//
//                if (intensity >= intensityThreshold) {
//                    float saturation = c.getSaturation();
//                    float z = ofMap(saturation, 0, 255, -100, 100);
//                    // We shrunk our image by a factor of 4, so we need to multiply our pixel
//                    // locations by 4 in order to have our mesh cover the openFrameworks window
//                    ofVec3f pos(x*4, y*4, z);
//                    ofVec3f pos(x*4, y*4, 0.0);
//                    mesh.addVertex(pos);
//                    mesh.addColor(c);
//                }
//           }
//       }
    
//    float connectionDistance = 30;
//    int numVerts = mesh.getNumVertices();
//    for (int a=0; a<numVerts; ++a) {
//        ofVec3f verta = mesh.getVertex(a);
//        for (int b=a+1; b<numVerts; ++b) {
//            ofVec3f vertb = mesh.getVertex(b);
//            float distance = verta.distance(vertb);
//            if (distance <= connectionDistance) {
//                // In OF_PRIMITIVE_LINES, every pair of vertices or indices will be
//                // connected to form a line
//                mesh.addIndex(a);
//                mesh.addIndex(b);
//            }
//        }
//    }

}

//--------------------------------------------------------------
void ofApp::update(){
    
        
    

}

//--------------------------------------------------------------
void ofApp::draw(){

//    ofColor centerColor = ofColor(85, 78, 68);
//    ofColor edgeColor(0, 0, 0);
//    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);
    
//    ofSetBackgroundColor(192, 6, 50);
    
    ofEnableDepthTest();

    rug.bind();

//    rug.draw(0,0);
    
    easyCam.begin();
        shader.begin();
        shader.setUniform1f("time", smoothedVol);
            plane.drawWireframe();

//        ofPushMatrix();
//            ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
//            mesh.draw();
//        ofPopMatrix();
    shader.end();
    easyCam.end();
    
    
    
    ofDisableDepthTest();

    
//    ofSetColor(gui->color);
//    ofDrawCircle(ofGetWidth()*0.5,ofGetWidth()*0.5,gui->radius);
//    ofSetColor(0);
//    ofDrawBitmapString(ofGetFrameRate(),20,20);

    
//
//    if(currentApp == IDLE) {
//                ofBackground(0);
//    } else if(currentApp == VIDEO) {
//                ofBackground(255,0,0);
//        // PLAY VIDEO
//    } else if(currentApp == GUI) {
//        // PAUSE VIDEO
//    }
    
}
//--------------------------------------------------------------
void ofApp::drawGui(ofEventArgs & args) {
    
    guiapp.setup();
    
    guiapp.draw();
    
//    ofDrawCircle(100, 100, 25);
    
    
//    parameters.add(radius.set("radius",50,1,100));
//    parameters.add(color.set("color",100,ofColor(0,0),255));
//    gui.setup(parameters);

}


//--------------------------------------------------------------
void ofApp::drawVideo(ofEventArgs & args) {
    
    vidapp.setup();

    vidapp.draw();
    
    
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch(key) {
            case 'f':
            ofToggleFullscreen();
            break;
            
    }

    
}

//--------------------------------------------------------------
//void ofApp::drawRandomInWindow(ofEventArgs &args){
//    ofPushStyle();
//    ofSetColor(ofRandom(128,255));
//    ofFill();
//    ofDrawRectangle(ofRandomuf()*20.f, ofRandomuf()*20.f, ofRandomuf()*80.f, ofRandomuf()*80.f);
//    ofPopStyle();
    
//}
//--------------------------------------------------------------
void ofApp::drawSeq( ofEventArgs & args){
    
//    if(windows.size() > 0)windows[0]->setWindowPosition(0, 600);



}
//--------------------------------------------------------------
void ofApp::drawPile( ofEventArgs & args){
    
    //if(windows.size() > 0)windows[0]->setWindowPosition(200,800);

//    rug.draw(0,0);
    
    
    
}
//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    float curVol = 0.0;
        float rms = 0.0;
    
    
//     samples are "interleaved"
    int numCounted = 0;
    
//    lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (int i = 0; i < bufferSize; i++){
        left[i]		= input[i*2]*0.5;
        right[i]	= input[i*2+1]*0.5;
        
        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        numCounted+=2;
    }
    
    curVol /= (float)numCounted;
    
    // this is how we get the root of rms :)
    curVol = sqrt( curVol );
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
    
    bufferCounter++;
    
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

// make new window = true
    // in update
    
    
//    float px = 200;
//    float py = 800-windows.size()*75;
//    if(py < 0) py = 0;
//    
    ofGLFWWindowSettings settings;
//    settings.width = 175;
//    settings.height = 75;
//    settings.setPosition(ofVec2f(px, py));
//    settings.resizable = false;
//    windows.push_back( ofCreateWindow(settings) );
//    windows.back()->setVerticalSync(false);
//    
//    if(windows.size() > 1) {
//       ofAddListener(windows.back()->events().draw, this,&ofApp::drawPile);
//        //        ofAddListener(windows.back()->events().draw, this,&ofApp::drawPile);
//        
//        
//    } else if (windows.size() == 8) {
//        ofAddListener(windows.back()->events().draw, this,&ofApp::drawSeq);
//        
//    }
    
    settings.visible = false;

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
