#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup(){
    cam.setVerbose(true);
    cam.setup(1280, 720);
    contourFinder.setMinAreaRadius(10);
    contourFinder.setMaxAreaRadius(150);
    
    
    threshold = 20;
    targetColor = (236,90,179);
    
    crash.load("crash.mp3");
    bass.load("kick-bass.mp3");
    snare.load("snare.mp3");
    tom1.load("tom-1.mp3");
    tom2.load("tom-2.mp3");
    tom3.load("tom-3.mp3");
    tom4.load("tom-4.mp3");
    
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    
    
    if(cam.isFrameNew()) {
        contourFinder.setTargetColor(targetColor, trackHs ? TRACK_COLOR_HS : TRACK_COLOR_RGB);
        contourFinder.setThreshold(threshold);
        contourFinder.findContours(cam);
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    //ofSetColor(255);
    ofSetColor(255, 255, 255);
    cam.draw(0, 0);
    
    ofSetLineWidth(20);
    //contourFinder.draw();
    
//    ofTranslate(8, 75);
//    ofFill();
//    ofSetColor(0);
//    ofDrawRectangle(-3, -3, 64+6, 64+6);
//    ofSetColor(targetColor);
//    ofDrawRectangle(0, 0, 64, 64);
    
    //draw the first rect
    ofSetColor(220, 56, 51);
    ofDrawRectangle(0, 0, 200, 200);
    //draw the first black line
    ofSetColor(0, 0, 0);
    ofDrawRectangle(0, 200, 200, 20);
    //draw the second rect
    ofSetColor(250, 222, 79);
    ofDrawRectangle(0, 220, 200, 200);
    //draw the second black line
    ofSetColor(0, 0, 0);
    ofDrawRectangle(0, 420, 200, 20);
    //draw the third rect
    ofSetColor(255, 255, 255);
    ofDrawRectangle(0, 440, 200, 280);
    //draw the third black line
    ofSetColor(0, 0, 0);
    ofDrawRectangle(200, 620, 20, 100);
    //draw the fourth rect
    ofSetColor(54, 70, 116);
    ofDrawRectangle(220, 620, 200, 100);
    //draw the fourth black line
    ofSetColor(0, 0, 0);
    ofDrawRectangle(420, 620, 20, 100);
    //draw the fifth rect
    ofSetColor(255, 255, 255);
    ofDrawRectangle(440, 620, 220, 100);
    //draw the fifth black line
    ofSetColor(0, 0, 0);
    ofDrawRectangle(640, 620, 20, 100);
    //draw the sixth rect
    ofSetColor(0, 0, 0);
    ofDrawRectangle(660, 620, 200, 100);
    //draw the sixth black line
    ofSetColor(0, 0, 0);
    ofDrawRectangle(860, 620, 20, 100);
    //draw the seventh rect
    ofSetColor(250, 222, 79);
    ofDrawRectangle(880, 620, 200, 100);
    
    int n = contourFinder.size();
    for(int i = 0; i < n; i++) {
        cv::RotatedRect ellipse = contourFinder.getFitEllipse(i);
        ofPushMatrix();
        ofVec2f ellipseCenter = toOf(ellipse.center);
        ofTranslate(ellipseCenter.x, ellipseCenter.y);
        ofSetColor(255, 255, 255);
        ofDrawEllipse(0, 0, 20, 20);
        ofPopMatrix();
        
        if ( ellipseCenter.x > 0 && ellipseCenter.x < 200 &&  ellipseCenter.y > 0 &&  ellipseCenter.y < 200) {
            crash.play();
            ofSetColor(180, 56, 51);
            ofDrawRectangle(0, 0, 220, 200);
            
        }
        if ( ellipseCenter.x > 0 && ellipseCenter.x < 200 &&  ellipseCenter.y > 220 &&  ellipseCenter.y < 420) {
            bass.play();
            ofSetColor(210, 220, 59);
            ofDrawRectangle(0, 220, 220, 200);
            
        }
        if ( ellipseCenter.x > 0 && ellipseCenter.x < 200 &&  ellipseCenter.y > 440 &&  ellipseCenter.y < 640) {
            snare.play();
            ofSetColor(200, 200, 200);
            ofDrawRectangle(0, 440, 220, 280);
            
        }
        if ( ellipseCenter.x > 200 && ellipseCenter.x < 400 &&  ellipseCenter.y > 620 &&  ellipseCenter.y < 720) {
            tom1.play();
            ofSetColor(34, 50, 96);
            ofDrawRectangle(220, 600, 200, 120);
            
        }
        if ( ellipseCenter.x > 420 && ellipseCenter.x < 640 &&  ellipseCenter.y > 620 &&  ellipseCenter.y < 720) {
            tom2.play();
            ofSetColor(205, 205, 205);
            ofDrawRectangle(440, 600, 200, 120);
            
        }
        if ( ellipseCenter.x > 660 && ellipseCenter.x < 860 &&  ellipseCenter.y > 620 &&  ellipseCenter.y < 720) {
            tom3.play();
            ofSetColor(20, 20, 20);
            ofDrawRectangle(660, 600, 200, 120);
            
        }
        if ( ellipseCenter.x > 880 && ellipseCenter.x < 1080 &&  ellipseCenter.y > 620 &&  ellipseCenter.y < 720) {
            tom4.play();
            ofSetColor(210, 220, 59);
            ofDrawRectangle(880, 600, 200, 120);
            
        }
    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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
    targetColor = cam.getPixels().getColor(x, y);
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
