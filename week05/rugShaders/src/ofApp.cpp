#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

#ifdef TARGET_OPENGLES
    shader.load("shadersES2/shader");
#else
    if(ofIsGLProgrammableRenderer()){
        shader.load("shadersGL3/shader");
    }else{
        shader.load("shadersGL2/shader");
    }
#endif
    
    int camWidth = 320;
    int camHeight = 240;
    
//    camera.setVerbose(false);
//    camera.initGrabber(camWidth, camHeight);
    
    movie.loadMovie("movie.mov");
    movie.play();
    
    image.loadImage("img1.jpg");
    imageMask.loadImage("mask.jpg");
    
//    fbo.allocate(camWidth, camHeight);
//    maskFbo.allocate(camWidth, camHeight);
    
//---------------------DISPLACEMENT MAP
    img.allocate(80, 60, OF_IMAGE_GRAYSCALE);
    
    plane.set(800, 600, 80, 60);
    plane.mapTexCoordsFromTexture(img.getTextureReference());


}

//--------------------------------------------------------------
void ofApp::update(){
//    camera.update();
    movie.update();
    
    //---------------------DISPLACEMENT MAP
    float noiseScale = ofMap(mouseX, 0, ofGetWidth(), 0, 0.1);
    float noiseVel = ofGetElapsedTimef();
    
    unsigned char * pixels = img.getPixels().getData();
    int w = img.getWidth();
    int h = img.getHeight();
    for(int y=0; y<h; y++) {
        for(int x=0; x<w; x++) {
            int i = y * w + x;
            float noiseVelue = ofNoise(x * noiseScale, y * noiseScale, noiseVel);
            pixels[i] = 255 * noiseVelue;
        }
    }
    img.update();

}

//--------------------------------------------------------------
void ofApp::draw(){

    //------------------------------------------- draw to mask fbo.
    maskFbo.begin();
    
    ofClear(255, 0, 0, 255);
    
    float imageMaskX = mouseX / (float)ofGetWidth();
    imageMaskX = ofClamp(imageMaskX, 0, 1);
    imageMaskX = -(imageMask.getWidth() - maskFbo.getWidth()) * imageMaskX;
    imageMask.draw(imageMaskX, 0);
    
    maskFbo.end();
    
    //------------------------------------------- draw to final fbo.
    fbo.begin();
    ofClear(0, 0, 0,255);
    
    shader.begin();
//    shader.setUniformTexture("tex0", camera.getTextureReference(), 1);
    shader.setUniformTexture("tex1", image, 2);
    shader.setUniformTexture("tex2", movie.getTextureReference(), 3);
    shader.setUniformTexture("imageMask", maskFbo.getTextureReference(), 4);
    
    // we are drawing this fbo so it is used just as a frame.
    maskFbo.draw(0, 0);
    
    shader.end();
    fbo.end();
    
    //------------------------------------------- 
//    ofSetColor(255);
//    camera.draw(5,5,320,240);
//    ofSetColor(ofColor::red);
//    ofDrawBitmapString("RED", 5+30, 5+30);
//
//    ofSetColor(255);
//    image.draw(320+10,5,320,240);
//    ofSetColor(ofColor::green);
//    ofDrawBitmapString("GREEN", 320+10+30,5+30);
//
//    ofSetColor(255);
//    movie.draw(320*2+15,5,320,240);
//    ofSetColor(ofColor::blue);
//    ofDrawBitmapString("BLUE", 320*2+5+30,5+30);
//
//    ofSetColor(255);
//    maskFbo.draw(320+10,240+10,320,240);
//    ofDrawBitmapString("RGB MASK", 320+10+30,240+10+30);
    
//    fbo.draw(320+10,240*2+15,320,240);
    fbo.draw(0,0,1000,768);
//    ofDrawBitmapString("Final FBO", 320+10+30,240*2+15+30);
    ofDrawBitmapString("Final FBO", 0,0);

    //---------------------DISPLACEMENT MAP
    // bind our texture. in our shader this will now be tex0 by default
    // so we can just go ahead and access it there.
    img.getTextureReference().bind();
    
    shader.begin();
    
    ofPushMatrix();
    
    // translate plane into center screen.
    float tx = ofGetWidth() / 2;
    float ty = ofGetHeight() / 2;
    ofTranslate(tx, ty);
    
    // the mouse/touch Y position changes the rotation of the plane.
    float percentY = mouseY / (float)ofGetHeight();
    float rotation = ofMap(percentY, 0, 1, -60, 60, true) + 60;
    ofRotate(rotation, 1, 0, 0);
    
    plane.drawWireframe();
    
    ofPopMatrix();
    
    shader.end();
    
    ofSetColor(ofColor::white);
    img.draw(0, 0);
    
}

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
