#include "wrapperApp.h"

////--------------------------------------------------------------
void wrapperApp::setup(){
    ofApp::setup();
    
    /**
     * Initialize the
     */
    isConnected = false;
    address = "http://localhost:3000/";
    status = "not connected";
    
    socketIO.setup(address);
    ofAddListener(socketIO.notifyEvent, this, &wrapperApp::gotEvent);
    
    ofAddListener(socketIO.connectionEvent, this, &wrapperApp::onConnection);
    
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
    ofDrawBitmapStringHighlight(wrapperApp::status, 20, 20);
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


/**
 * This function is called whenever the server receives an event
 */
void wrapperApp::gotEvent(string& name) {
    status = name;
}


/**
 * This function is called when the server connects to SocketIO
 */
void wrapperApp::onConnection () {
    isConnected = true;
    bindEvents();
}


/**
 * This function binds events to function, listening for the events
 */
void wrapperApp::bindEvents () {
    std::string serverEventName = "server-event";
    socketIO.bindEvent(serverEvent, serverEventName);
    ofAddListener(serverEvent, this, &wrapperApp::onServerEvent);
    
    std::string pingEventName = "ping";
    socketIO.bindEvent(pingEvent, pingEventName);
    ofAddListener(pingEvent, this, &wrapperApp::onPingEvent);
    
    std::string packageEventName = "flatPackage";
    socketIO.bindEvent(packageEvent, packageEventName);
    ofAddListener(packageEvent, this, &wrapperApp::onPackageEvent);
}


/**
 * A function that handles a server event. It logs the data
 */
void wrapperApp::onServerEvent (ofxSocketIOData& data) {
    ofLogNotice("ofxSocketIO", data.getStringValue("stringData"));
    ofLogNotice("ofxSocketIO", ofToString(data.getIntValue("intData")));
    ofLogNotice("ofxSocketIO", ofToString(data.getFloatValue("floatData")));
    ofLogNotice("ofxSocketIO", ofToString(data.getBoolValue("boolData")));
}


/**
 * A function that handles a Ping event. It emits an event
 */
void wrapperApp::onPingEvent (ofxSocketIOData& data) {
    ofLogNotice("ofxSocketIO", "ping");
    std::string pong = "pong";
    std::string param = "foo";
    socketIO.emit(pong, param);
}


/**
 * This function handles the package data that is received from SocketIO
 */
void wrapperApp::onPackageEvent (ofxSocketIOData& data) {
    ofLogNotice("ofxSocketIO", "package");
    ofLogNotice("ofxSocketIO", ofToString(data.getStringValue("image")));
}
