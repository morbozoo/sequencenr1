#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxJSON.h"
#include "ofxOsc.h"
#include "MidiInput.hpp"
#include "Particle.h"
#include "ParticleManager.h"
#include "Surface.hpp"
#include "SurfaceManager.hpp"
#include "Auxiliar.hpp"
#include "Grupo.hpp"
#include "GrupoManager.hpp"
#include "ofxMSATimer.h"
#include "ofxMidi.h"
#include "ofxSyphon.h"

class ofApp : public ofBaseApp, public ofxMidiListener {

	public:
		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

//------------------------0000--------------------------------------
    tri::SurfaceManagerRef mSurfaceManager;
    void        clearMesh();
    
    int         mTempParticleId;
    ofVec3f     tempPart;
    int         toMove;
    int         surfaceCounter;
    std::vector<int> editorTemporals;
    int         hoverParticle;
    bool        viewSurfaces;
    
    ofImage     fondo;
    bool        mHideFondo;
    
    void        clear();
    
    ofColor     color1;
    ofColor     color2;
    int         particleSize;

//------------------------SYPHON--------------------------------------
    ofxSyphonServer sifon;
    
//------------------------GRUPOS--------------------------------------
    tri::Grupo * tempGrupo = new tri::Grupo();
    std::vector<tri::Surface *>  tempSurfaces;
    tri::GrupoManagerRef mGrupos;
    bool mHideGroupEditor;
    int temporal;
    
//------------------------MIDI--------------------------------------
    MidiInput midiInput;
    
    void newMidiMessage(ofxMidiMessage& eventArgs);
    void setupMidi();
    ofxMidiIn sparkPublic;
    ofxMidiIn sparkPrivate;
    ofxMidiMessage midiMessage;
    
    int isLess9 = true;
    std::vector<ofColor *> colores1;
    std::vector<int *> velocidades1;
    
	
//------------------------GUI--------------------------------------
    ofxPanel        gui;
    bool            mHideGUI;
    
    void            setupGUI();

    ofxButton       mButtonResetMesh;
    
    ofxToggle       drawBoundingRectangle;
    ofxToggle       enableCreateSurface1;
    ofxToggle       enableMoveParticle2;
    ofxToggle       enableNewParticle3;
    ofxToggle       enableNewGroup4;
    ofxToggle       enableDeleteGroup5;
    

//------------------------JSON--------------------------------------
    
    ofxJSONElement      mJSON;
    void                saveJSON();
    void                loadJSON();
    
//------------------------JSON--------------------------------------
    
    AuxiliarRef            aux;
    
    int sequencerMode;

    
    ofxMSATimer timer;
};
