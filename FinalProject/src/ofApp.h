#pragma once


#include "ofMain.h"
#include "ofxAudioFile.h"


class ofApp: public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
        void exit();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        //define audio variables
        ofxAudioFile audiofile;
        
        double playhead;
        std::atomic<double> playheadControl;
        double step;
        double sampleRate;
        
        void audioOut(ofSoundBuffer & buffer);
    
        //define visual variables
        ofMesh mesh;
        ofEasyCam cam;
        ofColor col = (255,255,0);
    
        vector<ofVec3f> offsets;
        vector<ofVec3f> position;
        vector<ofVec3f> Camposition;
        vector<ofCylinderPrimitive> cy;
    
    //define sound player
    ofSoundPlayer mSound;
    
    //set camera
    ofPolyline polyline;
    ofPolyline polylineControl;
    
    
    float lookAtPointLength = 0.0;
    float camPosLength = 0.0;
    glm::vec3 lookAtPoint;
    glm::vec3 camPosition;
    
    bool cameraOnLine = false;
    int startP = 0;
    
    void creatNewPoint();
    int time;
};
