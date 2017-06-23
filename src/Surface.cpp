//
//  Surface.cpp
//  midiMap1
//
//  Created by ELVIRA on 07/06/17.
//
//

#include "Surface.hpp"
using namespace tri;

//--------------------------------------------------------------
Particle* Surface::getParticle(int c){
    return mParticles[c];
}

//--------------------------------------------------------------
ofVec3f Surface::getPosition(int c){
    return mParticles[c]->getPosition();
}

//--------------------------------------------------------------
int Surface::getIndex(int c){
    return mParticles[c]->getParticleId();
}

//--------------------------------------------------------------
void Surface::addParticle(tri::Particle *p){
    mParticles.push_back(p);
}

//--------------------------------------------------------------
void Surface::drawEdit(ofColor newColor){
    ofPushStyle();
    
    ofSetColor(newColor);
    ofSetLineWidth(2);
    ofDrawTriangle(mParticles[0]->getPosition().x, mParticles[0]->getPosition().y, mParticles[1]->getPosition().x, mParticles[1]->getPosition().y, mParticles[2]->getPosition().x, mParticles[2]->getPosition().y);
    
    ofNoFill();
    ofSetColor(0,250, 150, 70);
    ofDrawTriangle(mParticles[0]->getPosition().x, mParticles[0]->getPosition().y, mParticles[1]->getPosition().x, mParticles[1]->getPosition().y, mParticles[2]->getPosition().x, mParticles[2]->getPosition().y);
    
    ofPopStyle();
}

//--------------------------------------------------------------
void Surface::setSurfaceIndex(int newIndex){
    mSurfaceIndex = newIndex;
}

//--------------------------------------------------------------
int Surface::getSurfaceIndex(){
    return mSurfaceIndex;
}

//--------------------------------------------------------------

//--------------------------------------------------------------
void Surface::setColor(ofColor newColor){
    col = newColor;
}

//--------------------------------------------------------------
void Surface::setR(int r){
    if (col.r + r < 0) {
        col.r = 0;
    }else if(col.r + r > 255){
        col.r = 255;
    }else{
        col.r = col.r + r;
    }
    //ofLogNotice("ofApp::newMidiMessage") << ofToString(col);
}

//--------------------------------------------------------------
void Surface::setG(int g){
    if (col.g + g < 0) {
        col.g = 0;
    }else if(col.g + g > 255){
        col.g = 255;
    }else{
        col.g = col.g + g;
    }
    //ofLogNotice("ofApp::newMidiMessage") << ofToString(col);
}

//--------------------------------------------------------------
void Surface::setB(int b){
    if (col.b + b < 0) {
        col.b = 0;
    }else if(col.b + b > 255){
        col.b = 255;
    }else{
        col.b = col.b + b;
    }
    //ofLogNotice("ofApp::newMidiMessage") << ofToString(col);
}


//--------------------------------------------------------------
void Surface::draw(ofColor * newColor){
    
    ofPushStyle();
    
    ofSetColor(*newColor);
    ofDrawTriangle(mParticles[0]->getPosition().x, mParticles[0]->getPosition().y, mParticles[1]->getPosition().x, mParticles[1]->getPosition().y, mParticles[2]->getPosition().x, mParticles[2]->getPosition().y);

    ofPopStyle();
}
