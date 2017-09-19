#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
//    image.load("Colored_light.jpg");
    image.load("rashti-duzi-crop.jpg");
    image.resize(640,640);
    
    int width = image.getWidth();
    int height = image.getHeight();
   
    float step = 10.f;
    int stepWidth = width / step;
    int stepHeight = height / step;
    
    // create vertices
    for (int y = 0; y < stepHeight; y++){
        for (int x = 0; x < stepWidth; x++){
            mesh.addVertex( ofPoint( x*step - (width/2), y*step- (height/2) ,0));
            mesh.addTexCoord(ofPoint(x*step,y*step));
            
        }
    }
    
    // create triangles
    int w = stepWidth;
    for (int y = 0; y<stepHeight-1; y++){
        for (int x=0; x<stepWidth-1; x++){
            
            mesh.addIndex(x+y*w);
            mesh.addIndex(x+(y+1)*w);
            mesh.addIndex((x+1)+(y+1)*w);
            
            mesh.addIndex(x+y*w);
            mesh.addIndex((x+1)+(y+1)*w);
            mesh.addIndex((x+1)+y*w);			
            
        }
    }
    
    
//     ofSpherePrimitive::ofSpherePrimitive(float radius, int res, ofPrimitiveMode mode=OF_PRIMITIVE_TRIANGLE_STRIP)
    
    
    // setup gui
    gui.setup();
    gui.add(scaleFreq.setup("frequency", .1, 0, 1));
    gui.add(scaleTime.setup("phase", 1, 0, 10));
}

//--------------------------------------------------------------
void ofApp::update(){
    
    float scaledTime = ofGetElapsedTimef() * scaleTime;
    
    for( int i = 0; i < mesh.getNumVertices(); i++){
        
        ofPoint p = mesh.getVertex(i);
        float r = sqrt(p.x*p.x + p.y*p.y);
        p.z = 10 * sin( r*scaleFreq  + scaledTime) ;

        mesh.setVertex(i, p);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    
    ofSetColor(255);
    glEnable(GL_DEPTH_TEST);
    
    cam.begin();
    
    ofPushMatrix();
    
    ofSpherePrimitive(100, 100,OF_PRIMITIVE_TRIANGLE_STRIP);

    
    image.getTexture().bind();
    mesh.drawFaces();
    image.getTexture().unbind();
    
    ofTranslate(0,0,1);
    mesh.drawWireframe();
    ofPopMatrix();
    
    ofNoFill();
    ofDrawBox(0,0,0,image.getWidth());
    
    cam.end();
    
    
    // turn off depth test and draw gui
    glDisable(GL_DEPTH_TEST);
    gui.draw();
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
