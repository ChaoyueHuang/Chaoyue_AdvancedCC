#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    player.load("dog.mp4");
    player.play();
    
    for (int i = 0; i < 16; i++) {
        table[i] = ofRandom(0, 255);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    player.update();
    
    if (functionTwo == true) {
    if (player.isFrameNew()) {
        //getting pixels
        ofPixels pixels = player.getPixels();
        
        //scan all the pixels
        for (int y = 0; y < pixels.getHeight(); y++){
            for (int x = 0; x < pixels.getWidth(); x++){
                //getting pixel colot
                ofColor col = pixels.getColor(x, y);
                
                //change pixels' color
                float d = ofDist(x, y, ofGetMouseX(), ofGetMouseY());
                float adjustbrightness = ofMap(d, 0, 100, 8, 0);
                col.r *= adjustbrightness;
                col.g *= adjustbrightness;
                col.b *= adjustbrightness;
                
                //set color back to pixel
                pixels.setColor(x, y, col);
            }
        }
        //set pixel array to the image
        image.setFromPixels(pixels);
    }
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    //scale video
    //ofScale(zoomFactor, zoomFactor);
    
    player.draw(0,0);
    
    if (functionOne == true) {
    //getting the video's pixels
    ofPixels &pixels = player.getPixels();

    //define variables w,h equal to frame width and height
    int w = pixels.getWidth();
    int h = pixels.getHeight();

    //define circle variables
    int step = 20;
    int r = ofMap(ofGetMouseX(), 0, ofGetWidth(), 5, 10);
    int locx = 0;
    int locy = 0;
    //draw circle
    for (int x = 0; x < w; x = x + step) {
        ofColor color = pixels.getColor(x , h/2);
        ofSetColor(color);
        for (int i = 0; i < w; i = i + step)
         ofDrawCircle(locx, locy, r);
            for (int j = 0; j < h; j = j + step) {
            ofDrawCircle(locx, locy, r);
            locy = locy + step;
        }
        locx = locx + step;
        locy = 0;
    }
    }
    
    //draw the image
    ofSetColor(255, 255, 255);
    image.draw(0,0);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case 'z':
            functionOne = !functionOne;
            functionTwo = false;
            break;
        case 'x':
            functionTwo = !functionTwo;
            functionOne = false;
            break;
            
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
     if (functionOne == true) {
         //connect the speed variable with mouse X
         float mappedSpeed = ofMap(float(x), 0.0f, ofGetWidth(), 0, 2.0f);
         player.setSpeed(mappedSpeed);

         //connect the zoom factor with mouse Y
         zoomFactor = ofMap(float(y), 0.0f, ofGetHeight(), 0, 2.0f);
     }
    
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

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
