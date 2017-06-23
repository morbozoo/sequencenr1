#include "Particle.h"

namespace tri{
//--------------------------------------------------------------
     Particle::Particle( const Particle & obj){
        mPos = obj.mPos;
        mParticleIndex = obj.mParticleIndex;
        mCol = obj.mCol;
     }
    
//--------------------------------------------------------------
    Particle::Particle(){
        mParticleIndex = -1;
        mCol.set(255, 0, 0);
    }

//--------------------------------------------------------------
    void Particle::setParticleId(int index){
        mParticleIndex = index;
    }

//--------------------------------------------------------------
    int Particle::getParticleId(){
      return mParticleIndex;
    }

//--------------------------------------------------------------
    ofVec3f Particle::getPosition(){
        return mPos;
    }

//--------------------------------------------------------------
    void Particle::setPosition(ofVec3f pos){
        mPos = pos;
    }

//--------------------------------------------------------------
    void Particle::update(float time){

    }

//--------------------------------------------------------------
    void Particle::drawPoint(ofColor c, int newSize){
        ofPushStyle();
        ofSetColor(c);
        ofDrawEllipse(mPos.x, mPos.y, newSize, newSize);
        ofPopStyle();
    }
    
//--------------------------------------------------------------
    void Particle::drawSelectedPoint(){
        ofSetColor(255, 255, 0);
        ofDrawEllipse(mPos.x, mPos.y, 3, 3);
        ofNoFill();
        ofSetColor(255, 0, 0);
        ofDrawEllipse(mPos.x, mPos.y, 5, 5);
    }

//--------------------------------------------------------------
    void Particle::setColor(ofColor col){
        mCol = col;
    }
//--------------------------------------------------------------
    float Particle::getX(){
        return mPos.x;
    }
    
//--------------------------------------------------------------
    float Particle::getY(){
        return mPos.y;
    }
    
//--------------------------------------------------------------
    float Particle::getZ(){
        return mPos.z;
    }
    
//--------------------------------------------------------------

}
