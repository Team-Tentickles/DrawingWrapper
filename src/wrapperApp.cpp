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
    ofAddListener(queueUpdate, this, &wrapperApp::onDownloadFinish);
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
 * Handle the response of a finished download
 */
void wrapperApp::onDownloadFinish(int & downloadsLeft) {
    if (downloadsLeft < 1) {
        ofApp::resetAnimation();
    }
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
    
    std::string packageEventName = "flat-package";
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
    string artistImg11 = getImageUrlIfExists(data.getStringValue("artistImage11"));
    string artistImg12 = getImageUrlIfExists(data.getStringValue("artistImage12"));
    string artistImg21 = getImageUrlIfExists(data.getStringValue("artistImage21"));
    string artistImg22 = getImageUrlIfExists(data.getStringValue("artistImage22"));
    
    string startingAlbum11 = getImageUrlIfExists(data.getStringValue("albumImage11"));
    string startingAlbum12 = getImageUrlIfExists(data.getStringValue("albumImage12"));
    string startingAlbum21 = getImageUrlIfExists(data.getStringValue("albumImage21"));
    string startingAlbum22 = getImageUrlIfExists(data.getStringValue("albumImage22"));
    
    string mainArtist1 = getImageUrlIfExists(data.getStringValue("mainArtist1"));
    string mainArtist2 = getImageUrlIfExists(data.getStringValue("mainArtist2"));
    
    string supportingArtist1 = getImageUrlIfExists(data.getStringValue("mainArtist3"));
    string supportingArtist2 = getImageUrlIfExists(data.getStringValue("mainArtist4"));
    string supportingArtist3 = getImageUrlIfExists(data.getStringValue("mainArtist5"));
    string supportingArtist4 = getImageUrlIfExists(data.getStringValue("mainArtist6"));
    string supportingArtist5 = getImageUrlIfExists(data.getStringValue("mainArtist7"));
    string supportingArtist6 = getImageUrlIfExists(data.getStringValue("mainArtist8"));
    
    http.fetchURLToDisk(artistImg11, true, OUTPUT_DIRECTORY, "startingArtist11");
    http.fetchURLToDisk(artistImg12, true, OUTPUT_DIRECTORY, "startingArtist12");
    http.fetchURLToDisk(artistImg21, true, OUTPUT_DIRECTORY, "startingArtist21");
    http.fetchURLToDisk(artistImg22, true, OUTPUT_DIRECTORY, "startingArtist22");
    
    http.fetchURLToDisk(startingAlbum11, true, OUTPUT_DIRECTORY, "startingAlbum11");
    http.fetchURLToDisk(startingAlbum12, true, OUTPUT_DIRECTORY, "startingAlbum12");
    http.fetchURLToDisk(startingAlbum21, true, OUTPUT_DIRECTORY, "startingAlbum21");
    http.fetchURLToDisk(startingAlbum22, true, OUTPUT_DIRECTORY, "startingAlbum22");
    
    http.fetchURLToDisk(mainArtist1, true, OUTPUT_DIRECTORY, "mainArtist1");
    http.fetchURLToDisk(mainArtist2, true, OUTPUT_DIRECTORY, "mainArtist2");
    
    http.fetchURLToDisk(supportingArtist1, true, OUTPUT_DIRECTORY, "supportingArtist1");
    http.fetchURLToDisk(supportingArtist2, true, OUTPUT_DIRECTORY, "supportingArtist2");
    http.fetchURLToDisk(supportingArtist3, true, OUTPUT_DIRECTORY, "supportingArtist3");
    http.fetchURLToDisk(supportingArtist4, true, OUTPUT_DIRECTORY, "supportingArtist4");
    http.fetchURLToDisk(supportingArtist5, true, OUTPUT_DIRECTORY, "supportingArtist5");
    http.fetchURLToDisk(supportingArtist6, true, OUTPUT_DIRECTORY, "supportingArtist6");
    
//    http.fetchURLToDisk(ofToString(data.getStringValue("image")), true, OUTPUT_DIRECTORY);
}


/**
 * this function handles an HTTPResponse. Downloads a file to the temp directory
 * and passes the new URL to the loadImage function
 */
void wrapperApp::newResponse(ofxSimpleHttpResponse &r){
    
//    cout << "#########################################################" << endl;
//    cout << "download of " << r.url << " returned : "<< string(r.ok ? "OK" : "KO") << endl;
//    cout << "server reported size is " << r.serverReportedSize << endl;
//    cout << "server status is " << r.status << endl;
//    cout << "file content type is " << r.contentType << endl;
//    cout << "file name is " << r.fileName << endl;
    
    if(r.downloadToDisk){
        cout << "pending downloads: " << http.getPendingDownloads() << "\n";
        
        cout << "file was saved to " << r.absolutePath << endl;
        if (r.customField == "startingArtist11") {
            ofApp::startingArtist11Img.clear();
            ofApp::startingArtist11Img.load(r.absolutePath);
        }
        if (r.customField == "startingArtist12") {
            ofApp::startingArtist12Img.clear();
            ofApp::startingArtist12Img.load(r.absolutePath);
        }
        if (r.customField == "startingArtist21") {
            ofApp::startingArtist21Img.clear();
            ofApp::startingArtist21Img.load(r.absolutePath);
        }
        if (r.customField == "startingArtist22") {
            ofApp::startingArtist22Img.clear();
            ofApp::startingArtist22Img.load(r.absolutePath);
        }
        if (r.customField == "startingAlbum11") {
            ofApp::startingAlbum11Img.clear();
            ofApp::startingAlbum11Img.load(r.absolutePath);
        }
        if (r.customField == "startingAlbum12") {
            ofApp::startingAlbum12Img.clear();
            ofApp::startingAlbum12Img.load(r.absolutePath);
        }
        if (r.customField == "startingAlbum21") {
            ofApp::startingAlbum21Img.clear();
            ofApp::startingAlbum21Img.load(r.absolutePath);
        }
        if (r.customField == "startingAlbum22") {
            ofApp::startingAlbum22Img.clear();
            ofApp::startingAlbum22Img.load(r.absolutePath);
        }
        if (r.customField == "mainArtist1") {
            ofApp::mainArtist1Img.clear();
            ofApp::mainArtist1Img.load(r.absolutePath);
        }
        if (r.customField == "mainArtist2") {
            ofApp::mainArtist2Img.clear();
            ofApp::mainArtist2Img.load(r.absolutePath);
        }
        if (r.customField == "supportingArtist1") {
            ofApp::supportingArtist1Img.clear();
            ofApp::supportingArtist1Img.load(r.absolutePath);
        }
        if (r.customField == "supportingArtist2") {
            ofApp::supportingArtist2Img.clear();
            ofApp::supportingArtist2Img.load(r.absolutePath);
        }
        if (r.customField == "supportingArtist3") {
            ofApp::supportingArtist3Img.clear();
            ofApp::supportingArtist3Img.load(r.absolutePath);
        }
        if (r.customField == "supportingArtist4") {
            ofApp::supportingArtist4Img.clear();
            ofApp::supportingArtist4Img.load(r.absolutePath);
        }
        if (r.customField == "supportingArtist5") {
            ofApp::supportingArtist5Img.clear();
            ofApp::supportingArtist5Img.load(r.absolutePath);
        }
        if (r.customField == "supportingArtist6") {
            ofApp::supportingArtist6Img.clear();
            ofApp::supportingArtist6Img.load(r.absolutePath);
        }
        int downloads = http.getPendingDownloads();
        ofNotifyEvent(queueUpdate, downloads);
    }
}


/**
 * A utility function that checks the url for an image. If the url
 * exists, the app leaves the url alone. If it does not, it returns
 * a path to the default image.
 */
string wrapperApp::getImageUrlIfExists(string url) {
    cout << url;
    if (url == "") {
        ofFile f = ofFile("images/default.jpg");
        cout << "\n***************\n";
        cout << "file://" + f.getAbsolutePath();
        cout << "\n***************\n";
        return "file://" + f.getAbsolutePath();
    } else {
        return url;
    }
}
