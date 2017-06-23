//
//  GrupoManager.cpp
//  midiMap1
//
//  Created by DIEGO AMOZOO on 6/19/17.
//
//

#include "GrupoManager.hpp"
namespace tri{
//--------------------------------------------------------------
    GrupoManager::GrupoManager(){
        mTimer = 0.0;
        mTimeInc = 0.01;
        mTimerDir = 1;
        mStopTimer = false;
    }
    
//--------------------------------------------------------------
    void GrupoManager::addGrupo(Grupo *grup){
        mGrupos.push_back(grup);
    }
    
//--------------------------------------------------------------
    void GrupoManager::drawEditGrupos(){
        int cont = 0;
        ofColor newColor;
        for (auto & grupo : mGrupos) {
            switch (cont) {
                case 0:
                    newColor.set(150, 150, 20, 100);
                    break;
                case 1:
                    newColor.set(20, 150, 150, 100);
                    break;
                case 2:
                    newColor.set(150, 20, 150, 100);
                    cont = -1;
                    break;
            }
            grupo->drawEdit(newColor);
            cont ++;
        }
    }

//--------------------------------------------------------------
    void GrupoManager::drawInterface(){
        ofPushStyle();
        ofSetColor(200, 60, 150, 200);
        ofSetLineWidth(3);
        ofNoFill();
        for (int j = 0; j < RENGLONES; j++) {
            for (int i = 0; i < COLUMNAS; i++) {
                if (j*COLUMNAS + i < getNumberOfGroups()) {
                    ofDrawRectangle(500 + i * 17, 1083 + 17*j, 15, 15);
                }
            }
        }
        
        ofPopStyle();
    }
    
//--------------------------------------------------------------
    int GrupoManager::isInside(int x, int y){
        int resultado = -1;
        for (int j  = 0; j < RENGLONES; j++) {
            if (y > 1083 + 17*j && y < 1098 + 17*j ) {
                for (int i = 0; i < COLUMNAS; i++) {
                    if (x > 500 + i * 17 && x < 515 + i * 17) {
                        resultado = j * COLUMNAS + i;
                        if (resultado >= getNumberOfGroups()) {
                            resultado = -1;
                        }
                    }
                }
            }
            
        }
        return resultado;
    }
//--------------------------------------------------------------
    void GrupoManager::deleteGroup(int index){
        mGrupos.erase(mGrupos.begin() + index);
    }
    
    
//--------------------------------------------------------------
//--------------------------------------------------------------
    void GrupoManager::update(int nowTime){
        for (auto & grupo : mGrupos) {
            grupo->update(nowTime);
        }
    }
}


