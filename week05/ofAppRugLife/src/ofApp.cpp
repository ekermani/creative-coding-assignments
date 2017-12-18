#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // RUG LIFE
    // scene 1: type RUG LIFE, rug texture/ shaders , gui
    // scene 2: multi-window, rug old photos, stack of rugs, open cv jumping?
    // scene 3: flying carpet, audio
    
    // Scene States
    currentState = START;
    
    //------------------ scene 0 --------------------//
    
    // setup gui
    gui.setup(parameters);
    parameters.add(scale.set("font size", 36, 12, 72));
    parameters.add(rotate.set("rotation", 1, 0, 10));
//    parameters.add(color.set("text color", ))
    
    
//    ofBackground(0,0,0);
    ofNoFill();
    
    shader.load("shader.vert", "shader.frag");
    rug.load("rug.jpg");
    rug.update();
    

    //setup 3d font
    faceNavi3d.setup(OF_TTF_SANS,15,0.3);
    
    //Load three font-faces.//////////////////////////////////////////////////////////
    //setup 3d font by ofxTrueTypeFontUL2
    //Able to use all features. such as harbuzz or mixed fonts...
    
    //Setup 3d Face. (DisplayFontSize, DepthRate by fontsize)
    face.setup(scale,0.3);
    
    //load font for ofxTrueTypeFontUL2 ,
    face.loadFont("Yumin Demibold",128,true,true,0.3f,0,true)|| // windows 8.1
    face.loadSubFont("YuMincho")|| // osx mavericks
    face.loadSubFont("Meiryo")|| // windows 7
    face.loadSubFont("Hiragino Mincho ProN W3"); // osx
    
    //Load arabic face.   UNICODE:0x0600-0x06FF
    face.loadSubFont("Traditional Arabic",1,-0.04,0x0600,0x06FF)|| // windows
    face.loadSubFont("Geeza Pro",1,-0.04,0x0600,0x06FF,"arab");  // osx (Geeza need to set scriptTag.)
    
    //Set options.//////////////////////////////////////////////////////////////////////
    //face.setLineHeight(face.getFontSize()*2);
    //face.setLetterSpacing(0.1);
    //face.setTextDirection(UL2_TEXT_DIRECTION_RTL,UL2_TEXT_DIRECTION_TTB);
    
    //this made proportional fonts, these are OpenType features tag by "palt" or "vpal".
    //For the faces not having kerning pairs, such as Japanese fonts.
    face.useProportional(true);
    face.useVrt2Layout(true);
    face.setLineHeight(face.getFontSize()*1.5);
    

    //text////////////////////////////////////////////////////////////////////////////
    show.append(L"RUG LIFE\n");
    show.append(L"زندگی قالی\n");
    
    align = UL2_TEXT_ALIGN_V_TOP|UL2_TEXT_ALIGN_CENTER;
    strAlign="top-center [8]";
    strDirection="Left to Right (TTB)";
    
    glEnable(GL_CULL_FACE);//カリングON
    glCullFace(GL_BACK);//裏面をカリング
    glEnable(GL_DEPTH_TEST);
    
    renderingMode=true;
//    bRotation=false;
    
    //------------------ scene 1 --------------------//
    
    texture.load("rug.jpg");
    texture.getTexture().setTextureWrap( GL_REPEAT, GL_REPEAT );
    
    float width  = ofGetWidth() * .12;
    float height = ofGetHeight() * .12;
    plane.set( width*1.5, height*1.5 );
    
    
//    sequence.setup();
    sequence.loadSequence("frame", "png", 1, 8, 2);
    sequence.preloadAllFrames();    //this way there is no stutter when loading frames
    sequence.setFrameRate(1); //set to ten frames per second for Muybridge's horse.
    
    playing = true; //controls if playing automatically, or controlled by the mouse
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // scene 1
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // scene 0
    if (currentState == START) {
        
    ofSetVerticalSync(true);
    
    gui.draw();
//    ofSetColor(255);

    int w,h,x,y;
    x=100;
    y=100;
    w=mouseX-x;
    h=mouseY-y;

    //base line
    ofSetColor(255,127,255,255);
    ofDrawLine(0,y,ofGetWidth(),y);
    ofDrawLine(x,0,x,ofGetHeight());

    //cursor
//    ofSetColor(127,127,255,255);
//    ofDrawLine(mouseX,0,mouseX,ofGetHeight());
//    ofDrawLine(0,mouseY,ofGetWidth(),mouseY);

    //draw
        
    ofEnableDepthTest();
    glPushMatrix();{
        
//        gui.draw();

        if(renderingMode){
            light.enable();
            light.setPosition(ofGetWidth()*.5,ofGetHeight()*.5,ofGetWidth());
        }

//        if(bRotation){
        ofRectangle rc= face.getStringBoundingBox(show,x,y,w,h,align);
        glTranslatef(ofGetWidth()*.5,0,0);

//        glTranslatef(ofGetWidth()*.5,0,0);
            glRotatef(ofGetElapsedTimef()*10,0,1,0);
//            glTranslatef(x-rc.x -rc.width*.5,0,0);
        //}

//        if(renderingMode){
//            ofSetColor(255,255,255,255);
            face.draw3dString(show,x,y,0,w,h,align);
        //}else{
            ofSetColor(127,255,127,255);
            glPolygonMode(GL_FRONT, GL_LINE);
           // face.draw3dString(show,x,y,0,w,h,align);
            glPolygonMode(GL_FRONT, GL_FILL);
       // }

        light.disable();
        glDisable(GL_LIGHTING);
        
        rug.bind();
        easyCam.begin();
        shader.begin();
        shader.end();
        easyCam.end();

    }glPopMatrix();
        
    
        ofDisableDepthTest();


//    ofSetColor(255,255,0,255);
//    faceNavi3d.draw3dString("Rendering mode [Space]: "+ofToString(renderingMode?"Face":"Wire-frame"),50,ofGetHeight()-80,10);
//    faceNavi3d.draw3dString("Rotation [R]: "+ofToString(bRotation?"YES":"NO"),ofGetWidth()*.5,ofGetHeight()-80,10);
//    faceNavi3d.draw3dString("Wrap-mode [key w]: "+ ofToString(face.getWordWrap()?"Word-wrap":"Character-wrap"),50,ofGetHeight()-50,10);
//    faceNavi3d.draw3dString("Alignment-mode [key e]: "+ ofToString(face.getAlignByPixel()?"Alignment by Pixel":"Optimized"),50,ofGetHeight()-20,10);
//    faceNavi3d.draw3dString("Text-Alignment [key 0-9]: "+strAlign,ofGetWidth()*.5,ofGetHeight()-50,10);
//    faceNavi3d.draw3dString("Text-Direction [key a,z,s,x,d,c,f,v]: "+strDirection,ofGetWidth()*.5,ofGetHeight()-20,10);

//    face.getTexture().bind();
    
        } else if (currentState == SCENE_1) {
            
             plane.setPosition(ofGetWidth()*.2, ofGetHeight()*.25, 0);
//            sequence.draw(400, 400, 100, 100);
//            sequence.draw();
            sequence.getTextureForTime(ofGetElapsedTimef()).draw(0,0);

        } else if (currentState == SCENE_2) {
        }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch (key) {
        case '0':
            currentState = START;
            break;
        case 'f':
            ofToggleFullscreen();
            break;
        case ' ':
            currentState = SCENE_1;
//            shader.load("shader.vert", "shader.frag");
            break;
        case '1':
            currentState = SCENE_1;
//            shader.load("shader.vert", "shader.frag");
            break;
        case '2':
            currentState = SCENE_2;
//            shader.load("scene2shader.vert", "scene2shader.frag");
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
