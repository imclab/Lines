//
//  Control.cpp
//  firmataExample
//
//  Created by luisaph on 11/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "MIDIControl.h"

MIDIControl::MIDIControl(){
    //setup();
    
}

MIDIControl::MIDIControl(int _id, string _name){ 
    name = _name;
    id = _id;
    sendMIDIonUpdate = true;
    callibrating = false;
    setup();
    
}

void MIDIControl::setup(){
    channel = 1;
    cc = 1;
    note = 60;
    velocity = 60;
    currentValue = 0;
    minValue = 1024;
    maxValue = 1;
    outputMin = 0;
    outputMax = 127;
}

void MIDIControl::draw(){
    ofSetColor(255,255,255);
    int height = ofMap(currentValue, outputMin, outputMax, ofGetHeight(), 0);
    ofRect(id*100, 0, 100, height);
}

void MIDIControl::setValue(int value){
    currentValue = value;
    if(callibrating && value < minValue){
        minValue = value;
    }
    if(callibrating && value > maxValue && value < 1024){ //added < 1024 because getting highval at beginning for some reason.
        maxValue = value;
    }
}

bool MIDIControl::getCallibrating(){
    return callibrating;
}

void MIDIControl::setCallibrating(bool _c){
    callibrating = _c;
    //reset callibration
    if(callibrating){
        minValue = 1024;
        maxValue = 0;
    }
}

int MIDIControl::getValue(){
    return currentValue;
}
int MIDIControl::getMin(){
    return minValue;
}
int MIDIControl::getMax(){
    return maxValue;
}

int MIDIControl::getMIDIvalue(){
    return midiValue;
}

void MIDIControl::update(){ //method to be overriden. only pot sends value every time (and maybe not if value hasn't changed)
    /*
    midiValue = ofClamp(currentValue, minValue, maxValue);
    midiValue = ofMap(currentValue, getMin(), getMax(), outputMin, outputMax);
    //sendMIDI();
    */
}
 

void MIDIControl::sendMIDI(){   
    //MidiOut::getInstance().sendNoteOn(channel, midiValue);
    cout << "midiControl sendMidi" << endl;
    
    cout << "ID: " << id;
    cout << " minValue: " << getMin() << ", maxValue: " << getMax() << ", outputMin: " << outputMin << ", outputMax: " << outputMax << endl;
    cout << "ch: " << channel << ", cc: " << cc << ", midiVal: " << midiValue << endl; 
    
}

string MIDIControl::getName(){
    return name;
}






