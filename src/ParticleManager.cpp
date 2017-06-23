#include "ParticleManager.h"


namespace tri{

//--------------------------------------------------------------
    void ParticleManager::drawPoints(ofColor newColor, int newSize){
        ofPushStyle();
        for(auto & particle : mParticles){
            particle->drawPoint(newColor, newSize);
            if (!mhidePos) {
                ofSetColor(ofColor(255, 255, 255));
                ofDrawBitmapString(" "+ofToString(particle->getParticleId()), particle->getPosition().x + 5, particle->getPosition().y );
            }
        }
        ofPopStyle();
    }
    
//--------------------------------------------------------------
    void ParticleManager::drawMoveParticle(int particleId ,int newSize){
        ofPushStyle();
        Particle *particle = getParticle(particleId);
        particle->drawPoint(ofColor(255, 0, 0), newSize);
        ofSetColor(ofColor(255, 255, 255));
        ofNoFill();
        ofSetLineWidth(2);
        ofDrawCircle(particle->getPosition().x, particle->getPosition().y, 5);
        ofPopStyle();
    }
    
//--------------------------------------------------------------
    Particle * ParticleManager::getNearestParticle(ofVec3f pos){
        Particle * mTempP = NULL;
        int index = -1;
        for(auto & particle : mParticles){
            if(particle->getPosition().distance(pos) < 15){
                index = particle->getParticleId();
                return particle;
            }
        }
        return mTempP;
    }
    
    
//--------------------------------------------------------------
    Particle * ParticleManager::getParticle(int index){
        return mParticles.at(index);
    }
    
//--------------------------------------------------------------
    void ParticleManager::updateParticleColor(int index, ofColor col){
        mParticles.at(index)->setColor(col);
    }
    
//--------------------------------------------------------------
    void ParticleManager::addParticle(Particle * particle){
        particle->setParticleId(mParticles.size());
        mParticles.push_back(particle);
    }

//--------------------------------------------------------------
    void ParticleManager::setParticles(std::vector<Particle *> sParticles){
        mParticles = sParticles;
    }
    
//--------------------------------------------------------------
    std::vector<Particle *> ParticleManager::getParticles(){
        return mParticles;
    }
    
//--------------------------------------------------------------
    void ParticleManager::updateParticlePos(int index, ofVec3f pos){
        mParticles.at(index)->setPosition(pos);
        
    }
    
//--------------------------------------------------------------
    void ParticleManager::clear(){
        mParticles.clear();
        
    }
    
//--------------------------------------------------------------
    void ParticleManager::showPos(){
        mhidePos = !mhidePos;
        
    }
    
}




