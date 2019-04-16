#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    receiver1.setup(PORT1);
    receiver2.setup(PORT2);
    ofSetWindowTitle("Receiver App");
    
    //load gif
    gifloader1.load("gif5.gif");
    gifloader2.load("gif2.gif");
    
    //set background color
    ofBackground(255);
    
    //pdf
    oneShot = false;
    pdfRendering = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //get messages from mobile phone
    while(receiver1.hasWaitingMessages()){
        ofxOscMessage m1;
        if(receiver1.getNextMessage(m1)){
            if(m1.getAddress() == "/accxyz") {
                x = m1.getArgAsFloat(0);
                y = m1.getArgAsFloat(1);
                z = m1.getArgAsFloat(2);
//                                ofLogNotice() << "accellerometer x :" << x  << "accellerometer y :" << y << "accellerometer z :" << z << endl;

            }
        }
    }
    while(receiver2.hasWaitingMessages()){
        ofxOscMessage m2;
        if(receiver2.getNextMessage(m2)){
            if(m2.getAddress() == "/accxyz") {
                q = m2.getArgAsFloat(0);
                w = m2.getArgAsFloat(1);
//                e = m2.getArgAsFloat(2);
                ofLogNotice() << "accellerometer q :" << q  << endl;
               
            }
        }
    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //draw gif pictures
    int crt = ofGetElapsedTimef();
    if (( crt - lasttime) == 1) {
        lasttime = crt;
        m = (m+1) % 4;
    }
    ofSetColor(255, 255, 255, 255);
    ofImage img = gifloader1.pages[m];
    ofImage img2 = gifloader2.pages[m];
    ofPixels pix = img.getPixels();
    img.setFromPixels(pix);
    img.draw(x*1000+500,y*1000+500, 150,150); //move according to the  mobile phone's acceleration
    
    ofPixels pix2 = img2.getPixels();
    img2.setFromPixels(pix2);
    img2.draw(q*1000+500,w*1000+500,150,150); //move according to the  mobile phone's acceleration

    
    
    
    //set the condition of the fire and wave
    //if the x distance between the two fig is smaller than 0.5
    //trigger the fire and wave
    if( abs(q - x) < 0.5){
        ofPushMatrix();
        ofTranslate(x*1000+500+100, y*1000+550);
        fire();
        ofPopMatrix();
        edge = edge + 1;
        if (edge > 30) {
            edge = 0;
        }
    }
    
    if(abs(q - x) < 0.5) {
        
        ofPushMatrix();
        ofTranslate(q*1000+xpos+50, w*1000+500);
        wave();
        ofPopMatrix();
//        xpos = xpos - 10;
//        if (q*1000+xpos < 0) {
//            xpos = 300;
//        }
//        l = l + 0.1;
//        if (l > 30) {
//            l = 0;
//        }
        l = l - 0.5;
        if (l < 10) {
            l = 30;
        }

    }
   
    //pdf function
    if( oneShot ){
        ofBeginSaveScreenAsPDF("screenshot-"+ofGetTimestampString()+".pdf", false);
    }
    
    
}

void ofApp::pixel(int x, int y){
    ofPushMatrix();
    ofTranslate(edge, edge);
    //ofSetColor(0, 100, 0);
    ofDrawRectangle(x*edge, y*edge, edge, edge);
    ofPopMatrix();
    
}

void ofApp::pixelw(int x, int y){
    ofPushMatrix();
    ofTranslate(l, l);
    //ofSetColor(0, 100, 0);
    ofDrawRectangle(x*l, y*l, l, l);
    ofPopMatrix();
    
}

void ofApp::wave(){
    ofSetColor(214, 235, 254);
    pixelw(3, 0);
    pixelw(2, 1);
    ofSetColor(137, 194, 253);
    pixelw(3, 1);
    ofSetColor(214, 235, 254);
    pixelw(4, 1);
    pixelw(1, 2);
    ofSetColor(137, 194, 253);
    pixelw(2, 2);
    pixelw(3, 2);
    pixelw(4, 2);
    ofSetColor(214, 235, 254);
    pixelw(5, 2);
    pixelw(1, 3);
    ofSetColor(137, 194, 253);
    pixelw(2, 3);
    pixelw(3, 3);
    pixelw(4, 3);
    ofSetColor(214, 235, 254);
    pixelw(5, 3);
    pixelw(2, 4);
    ofSetColor(137, 194, 253);
    pixelw(3, 4);
    ofSetColor(214, 235, 254);
    pixelw(4, 4);
    pixelw(3, 5);
}


void ofApp::fire(){
    ofSetColor(255, 10, 30);
    //pixel(0, 0);
    pixel(1, 0);
    pixel(2, 0);
    pixel(3, 0);
    pixel(4, 0);
    //pixel(5, 0);
    //pixel(6, 0);
    //pixel(7, 0);
    pixel(8, 0);
    //pixel(9, 0);
    //pixel(10, 0);
    pixel(11, 1);
    pixel(0, 1);
    ofSetColor(255, 222, 5);
    pixel(0, 2);
    ofSetColor(255, 10, 30);
    pixel(0, 3);
    //pixel(0, 4);
    //pixel(0, 5);
    ofSetColor(255, 222, 5);
    pixel(1, 1);
    ofSetColor(255, 10, 30);
    ofSetColor(255, 222, 5);
    pixel(1, 2);
    ofSetColor(255, 10, 30);
    ofSetColor(253, 111, 7);
    pixel(1, 3);
    ofSetColor(255, 10, 30);
    pixel(1, 4);
    //pixel(1, 5);
    ofSetColor(253, 111, 7);
    pixel(2, 1);
    ofSetColor(255, 10, 30);
    ofSetColor(255, 222, 5);
    pixel(2, 2);
    ofSetColor(255, 10, 30);
    ofSetColor(255, 222, 5);
    pixel(2, 3);
    ofSetColor(255, 10, 30);
    pixel(2, 4);
    pixel(2, 5);
    pixel(3, 1);
    ofSetColor(253, 111, 7);
    pixel(3, 2);
    ofSetColor(255, 10, 30);
    ofSetColor(255, 222, 5);
    pixel(3, 3);
    ofSetColor(255, 10, 30);
    pixel(3, 4);
    pixel(3, 5);
    pixel(4, 1);
    pixel(4, 2);
    ofSetColor(255, 222, 5);
    pixel(4, 3);
    ofSetColor(255, 10, 30);
    pixel(4, 4);
    pixel(4, 5);
    pixel(5, 1);
    pixel(5, 2);
    ofSetColor(255, 222, 5);
    pixel(5, 3);
    ofSetColor(255, 10, 30);
    pixel(5, 4);
    pixel(5, 5);
    //pixel(6, 1);
    pixel(6, 2);
    pixel(6, 3);
    pixel(6, 4);
    //pixel(6, 5);
    //pixel(7, 1);
    //pixel(7, 2);
    pixel(7, 3);
    pixel(7, 4);
    //pixel(7, 5);
    //pixel(8, 1);
    //pixel(8, 2);
    pixel(8, 3);
    //pixel(8, 4);
    //pixel(8, 5);
    //pixel(9, 1);
    //pixel(9, 2);
    //pixel(9, 3);
    //pixel(9, 4);
    //pixel(9, 5);
    //pixel(10, 1);
    //pixel(10, 2);
    //pixel(10, 3);
    pixel(10, 4);
    //pixel(10, 5);
    
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    
    if( key=='r'){
        pdfRendering = !pdfRendering;
        if( pdfRendering ){
            ofSetFrameRate(12);  // so it doesn't generate tons of pages
            ofBeginSaveScreenAsPDF("recording-"+ofGetTimestampString()+".pdf", true);
        }else{
            ofSetFrameRate(60);
            ofEndSaveScreenAsPDF();
        }
    }
    
    if( !pdfRendering && key == 's' ){
        oneShot = true;
    }
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
