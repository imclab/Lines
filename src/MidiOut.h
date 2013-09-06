//
//  SoundPlayer.h
//  firmataExample
//
//  Created by luisaph on 11/19/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef firmataExample_SoundPlayer_h
#define firmataExample_SoundPlayer_h

#include "ofxMidi.h"
#include "ofMain.h"

//Singleton wrapper to allow different instances of MIDIControl to manage their own messaging. 
class MidiOut{
public:
    static MidiOut& getInstance(){
        static MidiOut instance;
        return instance;
    }
    void close();     
    void sendControlChange(int ch, int cc, int val);
    void sendNoteOn(int ch, int note);
    void sendNoteOff(int ch, int note);
    
private:
    MidiOut();
    MidiOut(MidiOut const&);    
    void operator=(MidiOut const&);
    
    std::string getStatus();
    ofxMidiOut midiOut;      
	
};

#endif


