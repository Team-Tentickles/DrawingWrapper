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
    
    ofxSimpleHttp::createSslContext();
    http.addCustomHttpHeader("Accept", "application/json"); //you can supply custom headers if you need to
    http.setCopyBufferSize(16);
    http.setSpeedLimit(1000);
    
    mainOutputSyphonServer.setName("Screen Output");
    
    //add download listener
    ofAddListener(http.httpResponse, this, &wrapperApp::newResponse);
}

//--------------------------------------------------------------
void wrapperApp::update(){
    ofApp::update();
    http.update();
}


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
 * This function handles the package data that is received from SocketIO.
 * Tells HTTP to download the image
 */
void wrapperApp::onPackageEvent (ofxSocketIOData& data) {
    ofLogNotice("ofxSocketIO", "package");
    http.fetchURLToDisk(ofToString(data.getStringValue("image")), true, OUTPUT_DIRECTORY);
}


/**
 * this function handles an HTTPResponse. Downloads a file to the temp directory
 * and passes the new URL to the loadImage function
 */
void wrapperApp::newResponse(ofxSimpleHttpResponse &r){
    
    cout << "#########################################################" << endl;
    cout << "download of " << r.url << " returned : "<< string(r.ok ? "OK" : "KO") << endl;
    cout << "server reported size is " << r.serverReportedSize << endl;
    cout << "server status is " << r.status << endl;
    cout << "file content type is " << r.contentType << endl;
    cout << "file name is " << r.fileName << endl;
    
    if(r.downloadToDisk){
        cout << "file was saved to " << r.absolutePath << endl;
        vector<string> v {
            r.absolutePath,
            r.absolutePath,
            r.absolutePath,
            r.absolutePath,
            r.absolutePath,
            r.absolutePath,
            r.absolutePath,
            r.absolutePath,
            r.absolutePath,
            r.absolutePath,
            r.absolutePath,
            r.absolutePath,
            r.absolutePath,
            r.absolutePath,
            r.absolutePath,
            r.absolutePath,
            r.absolutePath,
            r.absolutePath
        };
        loadImages(v);
    }
}
