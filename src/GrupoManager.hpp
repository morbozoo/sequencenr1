//
//  GrupoManager.hpp
//  midiMap1
//
//  Created by DIEGO AMOZOO on 6/19/17.
//
//

#ifndef GrupoManager_hpp
#define GrupoManager_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Grupo.hpp"
#define RENGLONES 4
#define COLUMNAS 25

namespace tri{
    
    class GrupoManager;
    
    typedef std::shared_ptr<GrupoManager> GrupoManagerRef;
    
    
    class GrupoManager {
    public:
        GrupoManager();
        
        static  GrupoManagerRef create(){ return std::make_shared<GrupoManager>(); }
        
        void addGrupo(Grupo * grup);
        
        int        getNumberOfGroups(){return mGrupos.size();}
        Grupo * getGrupo(int index){return mGrupos.at(index);}
        
        
        
        void setIncrTargetTimer(float val){mTimeInc = val;}
        
        void toggleTimer(bool timer){ if(!timer){mTimer = 0;} mStopTimer = timer; }
        
        void deleteGroup(int index);
        
        void clean();
        
        void drawEditGrupos();
        
        void drawInterface();
        
        void clearVectors();
        
        int isInside(int x, int y);
        
        
        void update(int nowTime);
        
        
        
    private:
        
        std::vector<Grupo *>         mGrupos;
        
        float                           mTimer;
        
        float                           mTimeInc;
        
        int                             mTimerDir;
        
        bool                            mStopTimer;
        
    };
}



#endif /* GrupoManager_hpp */
