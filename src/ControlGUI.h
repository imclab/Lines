//
//  InputGUI.h
//  firmataExample
//
//  Created by luisaph on 11/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef firmataExample_InputGUI_h
#define firmataExample_InputGUI_h

#include "ofMain.h"
#include "ofxUI.h"
#include "MIDIControl.h"


class ControlGUI{
public:    
    ControlGUI();
    ~ControlGUI();
    ControlGUI(int _id, int _width, int _xPos, int _yPos);
    
    void setup();
    void update();
    virtual void guiEvent(ofxUIEventArgs &e);
    void addTopWidgets();
    virtual void addControlSpecificWidgets() = 0; 
    void addBottomWidgets();
    void setValues(int current, int min, int max);  
    void loadSettings(string filename);
    void save(std::string filename);
    
    
    MIDIControl *control;
    ofxUICanvas *gui;
    ofxUIToggle *callibrate;
    
    
protected:        
    string id;
    int width;
    int xPos;
    int yPos;
    int controlWidth, dim;
    
    ofxUIMovingGraph *valueIn;
    ofxUIMovingGraph *midiOut;
    ofxUILabel *currentValue;
    ofxUILabel *midiValue;
    ofxUILabel *minValue;
    ofxUILabel *maxValue;
};


#endif
