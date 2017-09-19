#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//    paisley.setup();
//
//    for (int i = 0; i < NUMPAISLEY; i++) {
//        paisleyPark[i].setup();
//    }
    
    
    purplePaisley.push_back( PaisleyP() );  // add an element to the end
    purplePaisley[0].setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    
//    paisley.update();
    
    for (int i = 0; i < purplePaisley.size(); i++) {
        purplePaisley[i].update();
    }


}

//--------------------------------------------------------------
void ofApp::draw(){
    
//    paisley.draw();
    
//    ofBackground(128,0,128);
//    ofBackground(0);
    
    for(int i = 0; i < purplePaisley.size(); i++) {
        purplePaisley[i].draw();
        
    }
    
    //    moreBalls[0].draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    
//    if( key == 'c'){
//        
//        purplePaisley.push_back( PaisleyP() );  // add an element to the end
//        purplePaisley[ purplePaisley.size()-1 ].setup();
    
        // or create an object on the fly (only exists inside keyPressed; pass a copy through vector)
//        coolBall tempBall;
//        tempBall.setup();
//        moreBalls.push_back( tempBall );
        
    }
    
//    switch(key){
//        case 'c':
//            // do something
//            break;
//        case ' ':
//            break;
//        case OF_KEY_UP:
//            ofLog() << "key_up";
//            break;
//    }

//}

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
    
    
    purplePaisley.push_back( PaisleyP() );  // add an element to the end
    purplePaisley[ purplePaisley.size()-1 ].setup();

    

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
