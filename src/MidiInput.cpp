//
//  MidiInput.cpp
//  midiMap1
//
//  Created by DIEGO AMOZOO on 6/12/17.
//
//

#include "MidiInput.hpp"
//--------------------------------------------------------------
void MidiInput::setup() {
    mHideMidiInput = true;
    //--------settings------------------------------------
    numberOfCompasses = 1;
    
    tempoDenominator = 4;
    tempoNumerator = 4;
    ticksPerqNote = 24;
    
    
}


//--------------------------------------------------------------
void MidiInput::update(){
    
    
}


//--------------------------------------------------------------
void MidiInput::draw(){
    
    ofSetColor(255);
    
    if(midiMessage.status == MIDI_PITCH_BEND) {
        ofDrawRectangle(20, 202, ofMap(midiMessage.value, 0, MIDI_MAX_BEND, 0, ofGetWidth()-40), 20);
    }
    else {
        ofDrawRectangle(20, 202, ofMap(midiMessage.value, 0, 127, 0, ofGetWidth()-40), 20);
    }
    
    
    
    
    //------------------Interface---------------------
    ofPushStyle();
    ofEnableAlphaBlending();
    ofSetColor(50, 50, 50);
    ofDrawRectangle(0, 1081, 1920, 120);
    
    ofSetColor(150, 150, 150, 255);
    int cuentaCompas = -1;
    for (int k = 0; k < tempoqNotes-1; k++) {
        if (k % 4 == 0) {
            cuentaCompas ++;
        }
        ofPushStyle();
        ofNoFill();
        ofSetLineWidth(3);
        ofDrawRectangle(73*(k%4), 1083 + 17*cuentaCompas, 70, 15);
        ofPopStyle();
    }
    
    for (int i  = 0; i < numberOfCompasses; i++) {
        ofNoFill();
        ofSetLineWidth(3);
        if (i < 3) {
            ofDrawRectangle(300, 1083 + 17*(i+1), 15, 15);
        }
        ofDrawRectangle(300, 1083 + 17*i, 15, 15);
        ofSetColor(108, 189, 239, 255);
        ofFill();
        ofDrawRectangle(300, 1083 + 17*i, 15, 15);
        int cuartos = 0;
        for (int j = 0; j < NOTESPERCOMPASS; j++) {
            if (j%4 == 0) {cuartos++;}
            if (i*NOTESPERCOMPASS + j <= num32thNotes) {
                ofPushStyle();
                ofSetColor(108, 189, 239, 255);
                ofDrawCircle(10*cuartos + NOTESPERCOMPASS*j, 1090 + 17*i, 4);
                ofPopStyle();
            }else{
                ofSetColor(108, 189, 239, 100);
                ofDrawCircle(10*cuartos + NOTESPERCOMPASS*j, 1090 + 17*i, 5);
            }
        }
    }
    
    
    ofSetColor(150, 150, 150, 255);
    text << "ticks32: " << ticks32thNotePerBar << "bar: " << num32thNotes % 4 + 1, 20, 260;
    ofDrawBitmapString(text.str(), 350, 1093);
    text.str(""); // clear
    
    text << "tempoTicks: " << tempoTicks;
    ofDrawBitmapString(text.str(), 350, 1104);
    text.str(""); // clear
    
    text << "ticksforNote: " << ticksfor32thNote;
    ofDrawBitmapString(text.str(), 350, 1115);
    text.str(""); // clear
    
    text << "num32thNotes: " << num32thNotes;
    ofDrawBitmapString(text.str(), 350, 1126);
    text.str(""); // clear
    
    text << "tempoqNotes: " << tempoqNotes;
    ofDrawBitmapString(text.str(), 350, 1137);
    text.str(""); // clear
    
    text << "tempoBars: " << tempoBars;
    ofDrawBitmapString(text.str(), 350, 1148);
    text.str(""); // clear
    
    ofSetColor(108, 189, 239, 255);
    ofSetLineWidth(3);
    ofDrawLine(340, 1085, 340, 1150);
    ofDrawLine(490, 1085, 490, 1150);
    ofPopStyle();
}

//--------------------------------------------------------------
void MidiInput::mousePressed(ofMouseEventArgs &event){

    if (event.x > 300 && event.x < 315
        && event.y > 1083 + 17*numberOfCompasses && event.y < 1083 + 17*(numberOfCompasses+1)+15
        && numberOfCompasses<4) {
        numberOfCompasses++;
    }else if (event.x > 300 && event.x < 315
              && event.y > 1083 + 17*(numberOfCompasses-1) && event.y < 1083 + 17*(numberOfCompasses+1)+15
              && numberOfCompasses>1) {
        numberOfCompasses--;
    }
    
}
//--------------------------------------------------------------
void MidiInput::changeMode(){
    if (mHideMidiInput) {
        ofAddListener(ofEvents().mousePressed, this, &MidiInput::mousePressed);
        mHideMidiInput = false;
    }else{
        ofRemoveListener(ofEvents().mousePressed, this, &MidiInput::mousePressed);
        mHideMidiInput = true;
    }
}


//--------------------------------------------------------------
void MidiInput::newClockMessage(){
    tempoTicks += 1;
    ticksfor32thNote +=1;
    
    int _ticksPerqNote = (int) 24.0 * 4.0/tempoDenominator;
    ticksPerBar = tempoNumerator * ticksPerqNote;
    ticks32thNotePerBar = (int) ticksPerBar/8.0;
    ticksPer32thNote = (int) ticksPerqNote/8.0;
    
    if(ticksfor32thNote % ticksPer32thNote == 0 ) {
        // if(num32thNotes % 2 == 0) midiOut.sendNoteOff(1, 62, 0);
        // else  midiOut.sendNoteOn(1, 62, 127);
        num32thNotes  += 1;
    }
    
    
    
    if(tempoTicks % _ticksPerqNote == 0 ) {
        tempoqNotes += 1;
        tempoTicks = 0;
        if ((tempoqNotes) % (tempoNumerator*numberOfCompasses+1) == 0 ) {
            tempoBars += 1;
            tempoqNotes = 1;
            num32thNotes = 0;
            ticksfor32thNote = 0;
        }
    }
}
//--------------------------------------------------------------
void MidiInput::newStartMessage() {

    //ticks = 0;
    //qNotes = 0;
    //bars = 0;
    tempoTicks = 0;
    tempoqNotes = 1;
    tempoBars = 1;
    isPlaying = false;
    num32thNotes = 0;
    ticksfor32thNote = 0;
    
    isPlaying = true;
    
}

