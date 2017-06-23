//
//  JSON_IO.hpp
//  midiMap1
//
//  Created by ELVIRA on 08/06/17.
//
//

#ifndef JSON_IO_hpp
#define JSON_IO_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxJSON.h"
#include "Particle.h"

#endif /* JSON_IO_hpp */
namespace tri{
    class JSON_IO;
    
    typedef std::shared_ptr<JSON_IO> JSON_IORef;
    
    class JSON_IO{
    public:
        ofxJSONElement 		  mJSON;
        
        void    setup();
        
        std::vector<Particle *> loadParticles();
        void    loadGroups();
        
        void    saveParticles(std::vector<Particle *> sParticles);
        void    saveGroups();
        
    };
}
