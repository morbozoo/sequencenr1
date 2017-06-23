//
//  JSON_IO.cpp
//  midiMap1
//
//  Created by ELVIRA on 08/06/17.
//
//

#include "JSON_IO.hpp"
using namespace tri;
//--------------------------------------------------------------
void JSON_IO::setup(){
    
}

//--------------------------------------------------------------
std::vector<Particle *> JSON_IO::loadParticles(){
    std::vector<Particle *> loadedParticles;
    std::string file;
    file = "Particles.json";
    bool parsingSuccessful = mJSON.open(file);
    if(parsingSuccessful){
        ofLogNotice("ofApp::setup") << "successfully read: "<<file<<std::endl;
    }else{
        ofLogError("ofApp::setup")  << "Failed to parse JSON" << std::endl;
    }
    
    for (const Json::Value & points : mJSON["Particles"])  // iterate over "points"
    {
        float px   = points["x"].asFloat();
        float py   = points["y"].asFloat();

        Particle * tmpParticle = new Particle();
        tmpParticle->setPosition(ofVec3f(px, py, 0));
        
        loadedParticles.push_back(tmpParticle);
    }
    return loadedParticles;
}

//--------------------------------------------------------------
void JSON_IO::loadGroups(){
    
}

//--------------------------------------------------------------
void JSON_IO::saveParticles(std::vector<Particle *> sParticles){

    if(int particleNumber = sParticles.size() > 0){
        Json::Value points(Json::arrayValue);
        for (int j = 0; j < particleNumber; j++){
            Json::Value pos(Json::objectValue);
            pos["x"] = sParticles[j]->getPosition().x;
            pos["y"] = sParticles[j]->getPosition().y;
            points.append(pos);
        }
        ofLogNotice("ofApp::setup") <<points.size();
        mJSON["Particles"]  = points;
        if (!mJSON.save("Particles.json", true)){
            ofLogNotice("ofApp::setup") << "Particles.json written unsuccessfully.";
        }
        else{
            ofLogNotice("ofApp::setup") << "Particles.json written successfully.";
        }
    }
    mJSON.clear();
}

//--------------------------------------------------------------
void JSON_IO::saveGroups(){
    
}

