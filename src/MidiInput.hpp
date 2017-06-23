//
//  MidiInput.hpp
//  midiMap1
//
//  Created by DIEGO AMOZOO on 6/12/17.
//
//

#ifndef MidiInput_hpp
#define MidiInput_hpp

#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#define NOTESPERCOMPASS 16

class MidiInput{
    
public:
    
    void setup();
    void update();
    void draw();
    void changeMode();
    void mousePressed(ofMouseEventArgs& event);
    bool mHideMidiInput;
    
    void newClockMessage();
    void newStartMessage();
    
    stringstream text;
    
    ofxMidiIn sparkPublic;
    ofxMidiIn sparkPrivate;
    ofxMidiMessage midiMessage;
    
    int barIndex;
    
    int     tempoDenominator;
    float   ticksPerBar;
    int     tempoNumerator;
    int     ticksPerqNote;
    int     ticks32thNotePerBar;
    int     ticksPer32thNote = 0;
    int     tempoTicks;
    int     ticksfor32thNote;
    int     num32thNotes;
    int     tempoqNotes;
    int     tempoBars;
    bool    isPlaying;
    
    //--------settings------------------------------------
    int numberOfCompasses;
    
    
};

#endif /* MidiInput_hpp */
