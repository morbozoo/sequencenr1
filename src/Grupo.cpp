//
//  Grupo.cpp
//  midiMap1
//
//  Created by DIEGO AMOZOO on 6/15/17.
//
//

#include "Grupo.hpp"

using namespace tri;

//--------------------------------------------------------------
Surface* Grupo::getSurface(int c){
    return mSurfaces[c];
}

//--------------------------------------------------------------
void Grupo::addSurface(tri::Surface *s){
    mSurfaces.push_back(s);
}

//--------------------------------------------------------------
void Grupo::drawEdit(ofColor newColor){
    ofPushStyle();
    ofSetColor(newColor);
    for (auto & surface : mSurfaces) {
        surface->drawEdit(newColor);
    }
    ofPopStyle();
}

//--------------------------------------------------------------
void Grupo::setActive(int newStartTime, int newVelocidad){
    isActive = true;
    startTime = newStartTime;
    stopTime = startTime + 100;
    velocidad = newVelocidad * 2;
    //ofLogNotice("Grupo::setActive") << "mensaje: "<<newStartTime;
}

//--------------------------------------------------------------


//--------------------------------------------------------------
void Grupo::update(int nowTime){
    if (isActive) {
        alpha = ofMap(nowTime, startTime, stopTime, velocidad, 0, true);
        if (alpha == 0) {
            isActive = false;
        }
    }
}

//--------------------------------------------------------------
void Grupo::draw(int p, int v, ofColor * newColor){
    newColor->a = alpha;
    for (auto & surface : mSurfaces) {
        surface->draw(newColor);
    }
    ofLogNotice("Grupo::draw") << "mensaje: "<<ofToString(*newColor);
}

//--------------------------------------------------------------
void Grupo::clear(){
    mSurfaces.clear();
}

//--------------------------------------------------------------
int Grupo::getSize(){
    return mSurfaces.size();
}

//--------------------------------------------------------------
bool Grupo::getIsActive(){
    return isActive;
}

//--------------------------------------------------------------
std::vector<Surface *> Grupo::getSurfaces(){
    return mSurfaces;
}

//--------------------------------------------------------------
void Grupo::setSurfaces(std::vector<Surface *> newSurfaces){
    mSurfaces = newSurfaces;
}

//--------------------------------------------------------------
void Grupo::setColor(ofColor newColor){
    mColor = newColor;
}

//--------------------------------------------------------------
void Grupo::setCol(ofColor newColor){
    for (auto & surface : mSurfaces) {
        surface->setColor(newColor);
    }
}

//--------------------------------------------------------------
void Grupo::setR(int r){
    for (auto & surface : mSurfaces) {
        surface->setR(r);
    }
}

//--------------------------------------------------------------
void Grupo::setG(int g){
    for (auto & surface : mSurfaces) {
        surface->setG(g);
    }
}

//--------------------------------------------------------------
void Grupo::setB(int b){
    for (auto & surface : mSurfaces) {
        surface->setB(b);
    }
}
