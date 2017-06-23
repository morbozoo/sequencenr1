//
//  Auxiliar.hpp
//  midiMap1
//
//  Created by DIEGO AMOZOO on 6/12/17.
//
//

#ifndef Auxiliar_hpp
#define Auxiliar_hpp

#pragma once

#include <stdio.h>
#include "ofMain.h"


class Auxiliar;

typedef std::shared_ptr<Auxiliar> AuxiliarRef;

class Auxiliar{
public:
    
    Auxiliar( const Auxiliar & obj);
    Auxiliar();
    
    static AuxiliarRef create(){
        return std::make_shared<Auxiliar>();
    }
    
    void    drawBoundingBox();
    
private:

    
    
};




#endif /* Auxiliar_hpp */
