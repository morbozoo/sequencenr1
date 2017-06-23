//
//  SurfaceManager.cpp
//  midiMap1
//
//  Created by ELVIRA on 07/06/17.
//
//

#include "SurfaceManager.hpp"

namespace tri{
//--------------------------------------------------------------
    SurfaceManager::SurfaceManager(){
        mTimer = 0.0;
        mTimeInc = 0.01;
        mTimerDir = 1;
        mStopTimer = false;
    }
 
//--------------------------------------------------------------
    void SurfaceManager::addSurface(Surface * s){
        s->setSurfaceIndex(mSurfaces.size());
        mSurfaces.push_back(s);
    }


//--------------------------------------------------------------
    void SurfaceManager::cleanMesh(){
        mSurfaces.clear();
    }
//--------------------------------------------------------------
    void SurfaceManager::drawCreateSurface(std::vector<int> NewVertexIds, ofColor newColor1, ofColor newColor2, int newSize){
        drawEditSurfaces(newColor2);
        
        vertexIds = NewVertexIds;
        ofPushStyle();
        ofSetLineWidth(2);
        newColor2.a = 100;
        ofSetColor(newColor2);
        for (int i = 0; i < vertexIds.size(); i++) {
            Particle *tempo = getParticle(vertexIds[i]);
            tempo->drawPoint(newColor1, newSize);
            if (i>0) {
                Particle *tempo2 = getParticle(vertexIds[i-1]);
                ofSetColor(0, 150, 250);
                ofDrawLine(tempo->getX(), tempo->getY(), tempo2->getX(), tempo2->getY());
            }
            ofDrawCircle(tempo->getX(), tempo->getY(), newSize * 3);
        }
        ofPopStyle();
        
        drawMouseMoved();
    }
//--------------------------------------------------------------
    void SurfaceManager::drawMouseMoved(){
        ofPushStyle();
        ofSetColor(0, 150, 250, 150);
        ofSetLineWidth(2);
        ofVec3f posi;
        posi.set(ofGetMouseX(), ofGetMouseY());
        for (int i = 0; i < vertexIds.size(); i++) {
            ofVec3f tempo = getParticle(vertexIds[i])->getPosition();
            Particle *parti = getNearestParticle(ofVec3f(ofGetMouseX(), ofGetMouseY(), 0));
            if (parti != NULL) {
                posi = parti->getPosition();
            }
            ofDrawLine(tempo.x, tempo.y, posi.x, posi.y);
        }

        ofPopStyle();
    }
    
//--------------------------------------------------------------
    void SurfaceManager::drawEditSurfaces(ofColor newColor){
        for (auto & surface : mSurfaces) {
            surface->drawEdit(newColor);
        }
    }


//--------------------------------------------------------------
    void SurfaceManager::clearVectors(){
        vertexIds.clear();
    }

}
