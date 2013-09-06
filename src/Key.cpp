//
//  Key.cpp
//  firmataExample
//
//  Created by luisaph on 11/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Key.h"

Key::Key(){
    
}

Key::Key(int _id, string _name):MIDIControl(_id, _name){
    scaleLength = 8;
    root = 60;
    notePos = 0;
    isOn = false;
    threshold = 20;
    
    scale[0] = 0; 
    scale[1] = 2; 
    scale[2] = 4; 
    scale[3] = 7; 
    scale[4] = 9; 
    scale[5] = 12; 
    scale[6] = 14; 
    scale[7] = 16;
}


void Key::update(){
    if(!isOn){
        //cout << "here" << endl;
        if(currentValue > threshold){            
            int val = ofClamp(currentValue, outputMin, outputMax);
            notePos = ofMap(val, getMin(), getMax(), 0, scaleLength);             
            midiValue = getMIDInote(notePos);
            //TO DO: hack. in case not well callibrated...:
            midiValue = ofClamp(midiValue, 0, 127);            
            MidiOut::getInstance().sendNoteOn(channel, getMIDInote(notePos));
        }    
    }
    if(sendMIDIonUpdate){
        sendMIDI();
    }
    
}

void Key::sendMIDI(){
    if(isOn){
        if(currentValue < threshold){
            MidiOut::getInstance().sendNoteOff(channel, getMIDInote(notePos));            
            isOn = false;
        }
    }
    else{
        //cout << "here" << endl;
        if(currentValue > threshold){
            midiValue = getMIDIvalue();
            MidiOut::getInstance().sendNoteOn(channel, getMIDInote(notePos));
            isOn = true;
        }
        
    }
}

int Key::getMIDInote(int pos){
    return 127 - (root + scale[pos]);
}

int Key::getMIDIvalue(){
    return getMIDInote(notePos);
}

string Key::getType(){
    return "Key"; 
}

