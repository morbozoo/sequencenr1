//
//  Surface.hpp
//  midiMap1
//
//  Created by ELVIRA on 07/06/17.
//
//

#pragma once

#include "ofMain.h"
#include "Particle.h"

namespace tri{
    class Surface;
    
    typedef std::shared_ptr<Surface> SurfaceRef;
    
    class Surface{
    public:
        Surface(){}
        
        void setSurfaceIndex(int newIndex);
        int  getSurfaceIndex();
        Particle * getParticle(int c);
        
        ofVec3f    getPosition(int c);

        int        getIndex(int c);
        
        void       addParticle(Particle * p);
        
        void drawEdit(ofColor newColor);
        
        float sign (ofVec2f p1, ofVec2f p2, ofVec2f p3){
            return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
        }
        
        bool isPointInTriangle (ofVec2f pt){
            ofVec2f posA = getPosition(0);
            ofVec2f posB = getPosition(1);
            ofVec2f posC = getPosition(2);
            
            if(pt == posA||pt == posC||pt == posB)
                return false;
            
            bool b1, b2, b3;
            
            b1 = sign(pt, posA,  posB) < 0.0f;
            b2 = sign(pt, posB,  posC) < 0.0f;
            b3 = sign(pt, posC,  posA) < 0.0f;
            
            return ((b1 == b2) && (b2 == b3));
        }
        
        //------------------------------------
        void draw(ofColor * newColor);
        
        void setColor(ofColor newColor);
        void setR(int r);
        void setG(int g);
        void setB(int b);

        
    private:
        
        std::vector<Particle *>         mParticles;
        
        int                             mSurfaceIndex;
        
        ofColor col = ofColor(0, 0, 0);
    };
    
}
