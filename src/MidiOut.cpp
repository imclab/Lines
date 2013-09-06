//
//  SoundPlayer.cpp
//  firmataExample
//
//  Created by luisaph on 11/19/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "MidiOut.h"

MidiOut::MidiOut(){
    midiOut.listPorts();
    midiOut.openPort(0);
}


string MidiOut::getStatus(){
	stringstream text;
	text << "connected to port " << midiOut.getPort() 
    /*
    << " \"" << midiOut.getName() << "\"" << endl
    << "sending to channel " << channel << endl << endl
    << "note: " << note << endl
    << "velocity: " << velocity */<< endl;
	return text.str();
}

void MidiOut::close(){
	midiOut.closePort();
}

void MidiOut::sendControlChange(int ch, int cc, int val){
    midiOut.sendControlChange(ch, cc, val);
}

void MidiOut::sendNoteOn(int ch, int note){
    midiOut.sendNoteOn(ch, note);
}

void MidiOut::sendNoteOff(int ch, int note){
    midiOut.sendNoteOff(ch, note);
}


