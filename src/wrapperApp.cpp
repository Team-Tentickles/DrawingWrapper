#include "wrapperApp.h"

////--------------------------------------------------------------
void wrapperApp::setup(){
    ofApp::setup();
    mainOutputSyphonServer.setName("Screen Output");
}
//
////--------------------------------------------------------------
//void wrapperApp::update(){
//
//}
//
//--------------------------------------------------------------
void wrapperApp::draw(){
    ofApp::draw();
    mainOutputSyphonServer.publishScreen();
}

//--------------------------------------------------------------
void wrapperApp::keyPressed(int key){

}

//--------------------------------------------------------------
void wrapperApp::keyReleased(int key){

}

//--------------------------------------------------------------
void wrapperApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void wrapperApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void wrapperApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void wrapperApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void wrapperApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void wrapperApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void wrapperApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void wrapperApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void wrapperApp::dragEvent(ofDragInfo dragInfo){ 

}
