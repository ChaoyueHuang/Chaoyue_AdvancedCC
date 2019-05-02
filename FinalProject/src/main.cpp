#include "ofApp.h"

int main(){
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
    ofGLWindowSettings settings;
    settings.setSize(1920, 800);
    settings.setGLVersion(3, 2);
    ofCreateWindow(settings);

	//ofSetupOpenGL(1920, 800, OF_WINDOW);

	ofRunApp(new ofApp());
}
