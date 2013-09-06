//
//  System.h
//  firmataExample
//
//  Created by luisaph on 11/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef firmataExample_System_h
#define firmataExample_System_h

#include "Input.h"
#include "MIDIControl.h"
#include "Key.h"
#include "Pot.h"

enum DrawMode{
    TEMPO,
    WAVES,
    VALUES
};

class System{
public:
    System();
    ~System();
    void setup();
    void update();
    void draw();
    void close();
    
    void setCallibrate(bool value);
    void setSendMIDI(bool value);
    void toggleUseArduinoInput();
    void setDrawMode(DrawMode mode);
    
    
    
    int getNumControllers();
    
    
    //TO DO: should be private:
    
    DrawMode drawMode;
    Input input;
    bool smoothInput;
    
    int numPots; 
    int numKeys;
    vector<MIDIControl *> controllers;
    bool callibrating;
    
    
    
private:    
    void drawValues();
    void drawWaves();
    void drawTempo();
    
    bool useArduinoInput;
    bool sendMIDI;
    int lastDraw;
    int numControllers;
};




#endif
