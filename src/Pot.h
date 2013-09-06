//
//  Pot.h
//  firmataExample
//
//  Created by luisaph on 11/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef firmataExample_Pot_h
#define firmataExample_Pot_h
#include "MIDIControl.h"

enum PotMode{
    NORMAL, 
    SWITCH_OFF_BOTTOM,
    MIN_MAX_AREAS
};

class Pot: public MIDIControl{
public:
    Pot();
    Pot(int _id, string _name);
    void update();
    void sendMIDI();
    string getType();
    int getMIDIvalue();
    int zeroThreshold; 
    
    PotMode mode;
};

#endif
