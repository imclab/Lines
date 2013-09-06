//
//  Pot.cpp
//  firmataExample
//
//  Created by luisaph on 11/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Pot.h"

Pot::Pot(){
    
}

Pot::Pot(int _id, string _name):MIDIControl(_id, _name){    
    zeroThreshold = 30;
    mode = NORMAL;
    
}

void Pot::sendMIDI(){
    MidiOut::getInstance().sendControlChange(channel, cc, midiValue);
}

void Pot::update(){     
    currentValue = ofClamp(currentValue, outputMin, outputMax);   
    midiValue = ofMap(currentValue, getMin(), getMax(), outputMin, outputMax);
    midiValue = ofClamp(midiValue, outputMin, outputMax);
        
    //normalValue = ofClamp(currentValue, outputMin, outputMax);      
    //cout << borderAreaWidth << endl;
    /*
    switch(mode){   
        case NORMAL:
            midiValue = normalValue;
            break;
        case SWITCH_OFF_BOTTOM://under threshold, sends zero. after threshold, (outputMin, outputMax)              
            if(currentValue < zeroThreshold){                 
                midiValue = 0;                
            }
            else{
                midiValue = normalValue; //or from zerothreshold??
            }            
            break;
        case MIN_MAX_AREAS: //under and over thresholds, sends min and max respectively.             
            if(currentValue < bottomAreaPos){
                midiValue = outputMin;
            }
            else if(currentValue > topAreaPos){
                midiValue = outputMax;
            }
            else{
                midiValue = normalValue;
            } 
            break;          
    }*/ 
    
    if(sendMIDIonUpdate){
        sendMIDI();
    }
}

/*
 //this worked quite well...
 midiValue = ofMap(midiValue, getMin(), getMax(), outputMin*1.5, outputMax*1.5); //*2: want more 0's and 127's
 midiValue = ofClamp(midiValue, outputMin, outputMax);
 */ 


string Pot::getType(){
    return "Pot"; 
}

int Pot::getMIDIvalue(){
    return midiValue;
}

