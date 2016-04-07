#pragma once

#include "ofMain.h"
#include "ofApp.h"
#include "ofxSyphon.h"
#include "ofxSimpleHttp.h"
#include "ofxSocketIO.h"
#include "ofxSocketIOData.h"

#define OUTPUT_DIRECTORY "tempDownloads"

class wrapperApp : public ofApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofxSyphonServer mainOutputSyphonServer;
        ofxSimpleHttp http;
    
        ofxSocketIO socketIO;
        bool isConnected;
        void onConnection();
        void bindEvents();
        void gotEvent(string& name);
        void onServerEvent(ofxSocketIOData& data);
        void onPingEvent(ofxSocketIOData& data);
        void onPackageEvent(ofxSocketIOData& data);
        
        void newResponse(ofxSimpleHttpResponse &response);
    
    
    
        ofEvent<ofxSocketIOData&> serverEvent;
        ofEvent<ofxSocketIOData&> pingEvent;
        ofEvent<ofxSocketIOData&> packageEvent;

        std::string address;
        std::string status;
};
