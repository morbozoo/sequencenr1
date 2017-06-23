

#pragma once

#include "ofMain.h"

#include "Surface.hpp"
#include  "ParticleManager.h"

namespace tri{
    
    class SurfaceManager;
    
    typedef std::shared_ptr<SurfaceManager> SurfaceManagerRef;
    
    
    class SurfaceManager : public ParticleManager{
    public:
        SurfaceManager();
        
        static  SurfaceManagerRef create(){ return std::make_shared<SurfaceManager>(); }
        
        void generateSurfaces();
        
        void addSurface(Surface * sur);
        
        int        getNumberOfSurfaces(){return mSurfaces.size();}
        Surface * getSurface(int index){return mSurfaces.at(index);}
        
        
        
        void setIncrTargetTimer(float val){mTimeInc = val;}
        
        void toggleTimer(bool timer){ if(!timer){mTimer = 0;} mStopTimer = timer; }
        
        void cleanMesh();
        
        void drawCreateSurface(std::vector<int> vertexIds, ofColor newColor1, ofColor newColor2, int newSize);
        void drawMouseMoved();
        void drawEditSurfaces(ofColor newColor);
        
        void clearVectors();
        

        
    private:
        
        std::vector<Surface *>         mSurfaces;
        
        std::vector<int>                vertexIds;
        
        float                           mTimer;
        
        float                           mTimeInc;
        
        int                             mTimerDir;
        
        bool                            mStopTimer;
    };
    
}
