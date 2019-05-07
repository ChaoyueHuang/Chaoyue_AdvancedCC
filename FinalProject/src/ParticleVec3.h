#pragma once
#include "ofMain.h"

class ParticleVec3 {
    
public:
    ParticleVec3();

    void update();
    void draw();
    
  
    void throughOffWalls();
   
    
    void addAttractionForce(float x, float y, float z, float radius, float scale);

    
    ofVec3f position;
    ofVec3f velocity;
    ofVec3f acceleration;
    float friction;
    float radius;
    float mass;
    float minx, miny, minz;
    float maxx, maxy, maxz;
};
