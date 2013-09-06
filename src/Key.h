//
//  Key.h
//  firmataExample
//
//  Created by luisaph on 11/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef firmataExample_Key_h
#define firmataExample_Key_h
#include "MIDIControl.h"

class Key: public MIDIControl{
public:
    Key();
    Key(int _id, string _name);
    void update();
    void sendMIDI();
    string getType();
    int getMIDIvalue();
    
private:
    bool isOn;
    int threshold;
    int getMIDInote(int pos);
    int root;
    int notePos;
    int prevNotePos; 
    int scaleLength;//also see initialization of this in constructor
    int scale[8];
};


#endif
