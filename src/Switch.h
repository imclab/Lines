//
//  Switch.h
//  firmataExample
//
//  Created by luisaph on 12/4/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef firmataExample_Switch_h
#define firmataExample_Switch_h
#include "MIDIControl.h"

class Switch: public MIDIControl{
public:
    Switch();
    Switch(int id, string _name);
    void update();
    void sendMIDI();
    string getType();
private:
    bool send;
    int currentArea; //0: under threshold. 1: over threshold.
    int threshold;

};


#endif
