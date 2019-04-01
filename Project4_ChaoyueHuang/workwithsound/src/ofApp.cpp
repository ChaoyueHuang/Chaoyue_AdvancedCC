#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //load image file
    img.load("ghostchair.jpeg");
    // resize the canvas according to the image
    ofSetWindowShape(img.getWidth(), img.getHeight());
    
    //getting the video's pixels
    ofPixels &pixels = img.getPixels();

    //define variables w,h equal to frame width and height
    int w = pixels.getWidth();
    int h = pixels.getHeight();
    int step = 20;
    
    for (int x = 0; x < w; x = x + step) {
        for (int y = 0; y < h; y = y + step) {
            ofColor color = pixels.getColor(x , y);
            float saturation = color.getSaturation();
            if (saturation > 200) {
                int pos = xs + w/20*ys;
                rectLoc.push_back(ys);
            }
            ys++;
        }
        mArray.push_back(rectLoc);
        //ofLogNotice() << mArray[0].size() << endl;
        
        rectLoc.clear();
        ys = 0;
        xs++;
        
    }
    
    col_num = mArray.size();
    ofLogNotice() << col_num << endl;
    
//    for(int i = 0; i < mArray[5].size(); i++) {
//        //ofLogNotice() << mArray[0].size() << endl;
//        ofLogNotice() << mArray[5][i] << endl;
//    //}
//    }
    
    for (int i = 0; i < col_num; i++) {
        transparency.push_back(255);
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    //draw the image
    img.draw(0,0);
    
    //getting the video's pixels
    ofPixels &pixels = img.getPixels();
    
    //define variables w,h equal to frame width and height
    int w = pixels.getWidth();
    int h = pixels.getHeight();
    
    //define rectangles' variables
    int step = 20;
    int l = 20;

    
    //draw rectangles
    for (int x = 0; x < w; x = x + step) {
        for (int y = 0; y < h; y = y + step) {
        ofColor color = pixels.getColor(x , y);
        ofSetColor(color);
        ofDrawRectangle(x, y, l, l);
        
        }
    }
    
    //draw the moving line
    ofSetColor(255, 255, 255);
    ofSetLineWidth(2);
    ofDrawLine(lx, 0, lx, h);
    lx = lx + speed;
    if (lx > w) {
        lx = 0;
        for (int i = 0; i < col_num; i++) {
            transparency[i] = 255;
        }
        
    }
    //ofLogNotice() << lx << endl;
    
    if ( lx > 0 ) {
        for (int i = 0; i < mArray[0].size(); i++) {
            ofSetColor(255,255,255,transparency[0]);
            ofDrawRectangle(0, mArray[0][i]*l, l, l);
        }
        transparency[0] = transparency[0]-1;
    }

   if ( lx > l ) {
        for (int i = 0; i < mArray[1].size(); i++) {
            ofSetColor(255,255,255,transparency[1]);
            ofDrawRectangle(l, mArray[1][i]*l, l, l);
        }
        transparency[1] = transparency[1]-1;
    }
    
   if ( lx > l*2 ) {
        for (int i = 0; i < mArray[2].size(); i++) {
            ofSetColor(255,255,255,transparency[2]);
            ofDrawRectangle(l*2, mArray[2][i]*l, l, l);
        }
        transparency[2] = transparency[2]-1;
    }
    
    if ( lx > l*3 ) {
        for (int i = 0; i < mArray[3].size(); i++) {
            ofSetColor(255,255,255,transparency[3]);
            ofDrawRectangle(l*3, mArray[3][i]*l, l, l);
        }
        transparency[3] = transparency[3]-1;
    }
    
    if ( lx > l*4 ) {
        for (int i = 0; i < mArray[4].size(); i++) {
            ofSetColor(255,255,255,transparency[4]);
            ofDrawRectangle(l*4, mArray[4][i]*l, l, l);
        }
        transparency[4] = transparency[4]-1;
    }
    
    if ( lx > l*5 ) {
        for (int i = 0; i < mArray[5].size(); i++) {
            ofSetColor(255,255,255,transparency[5]);
            ofDrawRectangle(l*5, mArray[5][i]*l, l, l);
        }
        transparency[5] = transparency[5]-1;
    }
    if ( lx > l*6 ) {
        for (int i = 0; i < mArray[6].size(); i++) {
            ofSetColor(255,255,255,transparency[6]);
            ofDrawRectangle(l*6, mArray[6][i]*l, l, l);
        }
        transparency[6] = transparency[6]-1;
    }
    if ( lx > l*7 ) {
        for (int i = 0; i < mArray[7].size(); i++) {
            ofSetColor(255,255,255,transparency[7]);
            ofDrawRectangle(l*7, mArray[7][i]*l, l, l);
        }
        transparency[7] = transparency[7]-1;
    }
    if ( lx > l*8 ) {
        for (int i = 0; i < mArray[8].size(); i++) {
            ofSetColor(255,255,255,transparency[8]);
            ofDrawRectangle(l*8, mArray[8][i]*l, l, l);
        }
        transparency[8] = transparency[8]-1;
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
