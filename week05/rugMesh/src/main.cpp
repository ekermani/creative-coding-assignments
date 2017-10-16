#include "ofMain.h"
#include "ofApp.h"
#include "GuiApp.h"
#include "ofAppGLFWWindow.h"
#include "VideoApp.h"

    
int main( ){
    ofGLFWWindowSettings settings;
    
    // main window
    settings.width = 500;
    settings.height = 500;
    settings.setPosition(ofVec2f(350,0));
    settings.resizable = true;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    
    // GUI
    settings.width = 300;
    settings.height = 300;
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = false;
    shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(settings);
    
    // video window
    settings.width = 400;
    settings.height = 600;
    settings.setPosition(ofVec2f(1000,0));
    settings.resizable = false;
    shared_ptr<ofAppBaseWindow> videoWindow = ofCreateWindow(settings);

    // still --> popups (pile)
    settings.width = 175;
    settings.height = 75;
    settings.setPosition(ofVec2f(200,800));
    settings.resizable = false;
    shared_ptr<ofAppBaseWindow> pileWindow = ofCreateWindow(settings);
    
    // method to call window apps into main
    shared_ptr<ofApp> mainApp(new ofApp);
    //shared_ptr<GuiApp> guiApp(new GuiApp);
//    shared_ptr<VideoApp> videoApp(new VideoApp);
    
    // method to connect app to each window
    ofAddListener( guiWindow->events().draw, mainApp.get(), &ofApp::drawGui);
    ofAddListener( videoWindow->events().draw, mainApp.get(), &ofApp::drawVideo);
    ofAddListener( pileWindow->events().draw, mainApp.get(), &ofApp::drawPile);
    
    //ofRunApp(guiWindow, guiApp);
    ofRunApp(mainWindow, mainApp);
//    ofRunApp(videoWindow, videoApp);
    ofRunMainLoop();


}
