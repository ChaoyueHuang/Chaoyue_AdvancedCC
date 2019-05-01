#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    //ofsoudplayer
    //set target
    //set distance
    
    mSound.load("test.mp3");
    
    //set up visual
     ofSetFrameRate(60); //set framerate to 60
    mesh.setMode(OF_PRIMITIVE_LINES);
    mesh.enableColors();
    mesh.enableIndices();
    
    //float connectionDistance = 30;
    int numVerts = mesh.getNumVertices();
    for (int a=0; a<numVerts; ++a) {
        ofVec3f verta = mesh.getVertex(a);
        for (int b=a+1; b<numVerts; ++b) {
//            ofVec3f vertb = mesh.getVertex(b);
//            float distance = verta.distance(vertb);
           // if (distance <= connectionDistance) {
                // In OF_PRIMITIVE_LINES, every pair of vertices or indices will be
                // connected to form a line
                mesh.addIndex(a);
                mesh.addIndex(b);
            //}
        }
    }

    

    std::string filepath = ofToDataPath("test.mp3"); // mono original file
    //std::string filepath = ofToDataPath("tubophone.mp3"); // at the moment mp3 isn't working on ARM
    //std::string filepath = ofToDataPath("tubophone.ogg"); // ogg/vorbis
    //std::string filepath = ofToDataPath("tubophone.flac"); // FLAC

    audiofile.setVerbose(true); 
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    if( ofFile::doesFileExist( filepath ) ){
        audiofile.load( filepath );
        if (!audiofile.loaded()){
            ofLogError()<<"error loading file, double check the file path";
        }
    }else{
        ofLogError()<<"input file does not exists";
    }
    
    // audio setup for testing audio file stream 
	ofSoundStreamSettings settings;
    sampleRate = 44100.0;
    settings.setOutListener(this);
	settings.sampleRate = sampleRate;
	settings.numOutputChannels = 2;
	settings.numInputChannels = 0;
	settings.bufferSize = 512;
	ofSoundStreamSetup(settings);


    playhead = std::numeric_limits<int>::max(); // because it is converted to int for check
    playheadControl = -1.0;
    step = audiofile.samplerate() / sampleRate;
    
    for( int c=0; c<audiofile.channels(); ++c ){
        
        float max = ofGetWidth()*10;
        
        for( int x=0; x<max; x = x+10){
            
            int n = ofMap( x, 0, max, 0, audiofile.length(), true );
            float val = audiofile.sample( n, 0 );
            float y = ofMap( val, -1.0f, 1.0f, -ofGetHeight()*5, ofGetHeight()*5 );
            ofVec3f pos(x, ofGetHeight()/2, y);
            ofVec3f Campos(x, 0, y);
            mesh.addVertex(pos);
            position.push_back(pos);
            Camposition.push_back(Campos);
            //cout << mesh.getNumVertices() << endl;
            
            mesh.addColor(col);
            //cout << col << endl;
            //create offset to each vertex
            offsets.push_back(ofVec3f(ofRandom(0,100000), ofRandom(0,100000), ofRandom(0,100000)));
            //zloc++;
        }
        
    }
    
    //set all the cylinders
    for(int i = 0; i <position.size(); i++) {
        cy.resize(position.size());
        cy[i].set(4.0f, ofRandom(50.0f, 180.0f), 12, 4);
        cy[i].setPosition(position[i]);
        cy.push_back(cy[i]);
            }
    
   
    //camera point
    for (int i = 0; i < 3; ++i)
    {
        glm::vec3 targetPoint;
        targetPoint = position[i];
        polyline.curveTo(targetPoint,500);
        polylineControl.addVertex(targetPoint);
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
//    int numVerts = mesh.getNumVertices();
//    for (int i=0; i<numVerts; ++i) {
//        ofVec3f vert = mesh.getVertex(i);
//
//        float time = ofGetElapsedTimef();
//        float timeScale = 5.0;
//        float displacementScale = 0.75;
//        ofVec3f timeOffsets = offsets[i];
//
//
//        vert.x += (ofSignedNoise(time*timeScale+timeOffsets.x)) * displacementScale;
//        vert.y += (ofSignedNoise(time*timeScale+timeOffsets.y)) * displacementScale;
//        vert.z += (ofSignedNoise(time*timeScale+timeOffsets.z)) * displacementScale;
//        mesh.setVertex(i, vert);
//    }
    float totalLength = polyline.getLengthAtIndex(polyline.size() - 1);
    
    if (lookAtPointLength < totalLength)
    {
        lookAtPointLength += ofMap(totalLength - lookAtPointLength, 500, 0, 5.0f, 0.0f);
    }
    
    
    float camPosLength = lookAtPointLength - 10;
    
    if (camPosLength < 0) {
        camPosLength = lookAtPointLength;
    }
    
    lookAtPoint = polyline.getPointAtLength(lookAtPointLength);
    camPosition = polyline.getPointAtLength(camPosLength);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofColor centerColor = ofColor(85, 78, 68);
    ofColor edgeColor(0, 0, 0);
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);
    
    creatNewPoint();
    
    cam.begin();
    //cam.setTarget(glm::vec3 (Camposition[1])); //set camera
    //camera stuff
    cam.setScale(5);
    //cam.setDistance(800);
    ofSetColor(255,255,255);
    polyline.draw();

    for (auto& point : polylineControl)
    {
        ofSetColor(255,0,0);
        ofDrawSphere(point, 10);
    }
    
    
    cam.lookAt(lookAtPoint);
    ofSetColor(255,255,0,10);
    ofDrawSphere(camPosition, 50);
    
    
    if(cameraOnLine){
        cam.setPosition(camPosition);
    }
    //camera stuff end
    
    ofPushMatrix();
    //ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
    
    
    
    
    mesh.draw();
    
    
    //draw the cylinders
    for(int n = 0; n <position.size(); n++) {
        cy[n].drawWireframe();
    }
    
    
    ofPopMatrix();
    cam.end();
    
    //text
    ofDrawBitmapString( audiofile.path(), 10, 20 );
    
    ofDrawBitmapString ( "press SPACEBAR to play, press L to load a sample", 10, ofGetHeight()-20);
}

//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer & buffer){
    
    // really spartan and not efficient sample playing, just for testing
    
    if( playheadControl >= 0.0 ){
        playhead = playheadControl;
        playheadControl = -1.0;
    }
    
    for (size_t i = 0; i < buffer.getNumFrames(); i++){
        
        int n = playhead;
        
        if( n < audiofile.length()-1 ){
            
            for( size_t k=0; k<buffer.getNumChannels(); ++k){
                if( k < audiofile.channels() ){
                    float fract = playhead - (double) n;
                    float s0 = audiofile.sample( n, k );
                    float s1 = audiofile.sample( n+1, k );
                    float isample = s0*(1.0-fract) + s1*fract; // linear interpolation
                    buffer[i*buffer.getNumChannels() + k] = isample;
                }else{
                    buffer[i*buffer.getNumChannels() + k] = 0.0f;
                }
            }
            
            playhead += step;
        
        }else{
            buffer[i*buffer.getNumChannels()    ] = 0.0f;
            buffer[i*buffer.getNumChannels() + 1] = 0.0f;
            playhead = std::numeric_limits<int>::max();
        }

    }
}
		
		

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    audiofile.load( dragInfo.files[0] );
}

//--------------------------------------------------------------
void ofApp::exit(){
    ofSoundStreamClose();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == ' ') playheadControl = 0.0;
    
    if( key == 'l' || key=='L'){
       //Open the Open File Dialog
        ofFileDialogResult openFileResult= ofSystemLoadDialog("select an audio sample"); 
        //Check if the user opened a file
        if (openFileResult.bSuccess){
            string filepath = openFileResult.getPath();            
            audiofile.load ( filepath );
            step = audiofile.samplerate() / sampleRate;
            ofLogVerbose("file loaded");
        }else {
            ofLogVerbose("User hit cancel");
        }
    }
    if( key == 'p' || key=='P') {
        mSound.play();
    }
    if( key == 's' || key=='S') {
        mSound.setPaused(true);
    }
    if( key == 'b' || key=='B') {
        mSound.setPaused(false);
    }
    if( key == 'j' || key=='J') {
        
        glm::vec3 targetPoint;
        targetPoint = position[startP];
        polyline.curveTo(targetPoint, 500);
        polylineControl.addVertex(targetPoint);
        startP++;
    }
    if( key == '1') {
        cameraOnLine = true;
    }
    if( key == '2') {
        cameraOnLine = false;
    }
    
        
}

//--------------------------------------------------------------
void ofApp::creatNewPoint(){
    time = mSound.getPositionMS()/1000;
    glm::vec3 targetPoint;
    targetPoint = position[floor(time)];
    polyline.curveTo(targetPoint, 500);
    polylineControl.addVertex(targetPoint);
    
    
}

void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}


