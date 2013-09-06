//
//  Control.h
//  firmataExample
//
//  Created by luisaph on 11/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef firmataExample_Control_h
#define firmataExample_Control_h
#include "MidiOut.h"


class MIDIControl{
public:
    MIDIControl();
    MIDIControl(int _id, string _name);
    void setup();
    void draw();
    void setCallibrating(bool _c);
    bool getCallibrating();
    void setValue(int value);
    int  getValue();
    int  getMin();
    int  getMax();
    virtual void update();
    virtual void sendMIDI() = 0;  
    virtual string getType() = 0;
    virtual int getMIDIvalue() = 0;
    string getName();
    void close();
    
    int outputMin, outputMax; //TO DO: lazy to make getters right now...     
    int channel, cc, note, velocity; 
    bool sendMIDIonUpdate;
    int currentValue, minValue, maxValue;  
    
    
    
protected:  
    int midiValue;
    string name;
    int id;    
    bool callibrating;
    
    
};
#endif
