//
//  Grupo.hpp
//  midiMap1
//
//  Created by DIEGO AMOZOO on 6/15/17.
//
//

#ifndef Grupo_hpp
#define Grupo_hpp


#endif /* Grupo_hpp */

#pragma once

#include "ofMain.h"
#include "Surface.hpp"


namespace tri{
    class Grupo;
    
    typedef std::shared_ptr<Grupo> GrupoRef;
    
    class Grupo{
    public:
        Grupo(){}
        
        Surface * getSurface(int c);
        int     getSize();

        void       addSurface(Surface * s);
        
        void drawEdit(ofColor newColor);
        
        void draw(int p, int v, ofColor * newColor);
        
        
        void clear();
        
        std::vector<Surface *> getSurfaces();
        void setSurfaces(std::vector<Surface *> newSurfaces);
        
        void setColor(ofColor newColor);
        
        
        //--------------------------------
        void update(int nowTime);
        
        void setCol(ofColor newColor);
        void setR(int r);
        void setG(int g);
        void setB(int b);
        
        void setActive(int newStartTime, int newVelocidad);
        
        bool getIsActive();
        
        
    private:
        
        
        std::vector<Surface *>         mSurfaces;
        
        ofColor                        mColor = ofColor(0, 0, 0);
        
        //--------------------------------
        
        bool isActive = false;
        
        int alpha = 255;
        
        int startTime;
        int stopTime;
        
        int velocidad;
        
    };
    
}
