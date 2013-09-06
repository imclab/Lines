//
//  Switch.cpp
//  firmataExample
//
//  Created by luisaph on 12/4/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Switch.h"

Switch::Switch(){
    
}

Switch::Switch(int _id, string _name):MIDIControl(_id, _name){
    threshold = 50;
    currentArea = 0;
}

void Switch::sendMIDI(){
    if(send){
        MidiOut::getInstance().sendControlChange(channel, cc, 127); //TO DO: check if this is how buttons are implemented in MIDI.
    }
    
}

void Switch::update(){   
    int value = ofClamp(midiValue, getMin(), getMax());
    bool send = false; 
    if(value < threshold){ //change from 0 to 1
        if(currentArea == 1){
            send = true; 
        }  
        currentArea = 0;              
    }
    else if(value >= threshold){ //change from 1 to 0
        if(currentArea == 0){
            send = true;
        }
        currentArea = 1;        
    }
    if(sendMIDIonUpdate){
        sendMIDI();
    }
}

string Switch::getType(){
    return "Switch"; 
}

