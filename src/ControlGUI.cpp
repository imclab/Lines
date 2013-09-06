//
//  ControlGUI.cpp
//  firmataExample
//
//  Created by luisaph on 11/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "ControlGUI.h"

ControlGUI::~ControlGUI(){
    delete gui;
    delete control;
}

ControlGUI::ControlGUI(int _id, int _width, int _xPos, int _yPos){
    id = ofToString(_id);
    width = _width; 
    xPos = _xPos;
    yPos = _yPos;
    controlWidth = width - OFX_UI_GLOBAL_WIDGET_SPACING * 2;
    dim = 16; 
    gui = new ofxUICanvas(xPos, yPos, width, ofGetWindowHeight());    
    
}

void ControlGUI::setup(){
    gui->setColorBack(ofColor(0,35));
    string a = "INPUT A" + ofToInt(id);//TO DO: look up concat in c... + seems to be binary.
    string b = " " + control->getName(); 
    gui->addWidgetRight(new ofxUILabel(a + b , OFX_UI_FONT_MEDIUM));    
    
    addTopWidgets();
    addControlSpecificWidgets(); //virtual method, redefined in subclasses.
    addBottomWidgets(); 
    
}

void ControlGUI::addTopWidgets(){
    vector<float> buffer; 
    for(int i = 0; i < 256; i++)
    {
        buffer.push_back(0.0);
    }
    valueIn = (ofxUIMovingGraph *) gui->addWidgetDown(new ofxUIMovingGraph(controlWidth, 60, buffer, 256, 0, 100, "INPUT"));
    currentValue = new ofxUILabel("value: 000", OFX_UI_FONT_SMALL);
    gui->addWidgetDown(currentValue);
    
    minValue = new ofxUILabel("min: 000", OFX_UI_FONT_SMALL);
    gui->addWidgetRight(minValue);
    
    maxValue = new ofxUILabel("max: 000", OFX_UI_FONT_SMALL);
    gui->addWidgetRight(maxValue);    
    
    callibrate = new ofxUIToggle( "callibrate", control->getCallibrating(), dim, dim);      
    gui->addWidgetDown(callibrate);   
    
    gui->addWidgetDown(new ofxUILabel("MIDI OUT", OFX_UI_FONT_MEDIUM));   
    gui->addWidgetRight(new ofxUIToggle("on", control->sendMIDIonUpdate, dim, dim)); 
    
    /*
     //TO DO: allow change of control type 
     vector<string> names; 
     names.push_back("Key");
     names.push_back("Pot");    
     gui->addRadio("control type", names, OFX_UI_ORIENTATION_VERTICAL, dim, dim);
     */
    
    midiValue = new ofxUILabel("midiValue: 000 ", OFX_UI_FONT_SMALL);
    gui->addWidgetDown(midiValue);
    
    vector<float> buffer2; 
    for(int i = 0; i < 256; i++)
    {
        buffer2.push_back(0.0);
    }
    midiOut = (ofxUIMovingGraph *) gui->addWidgetDown(new ofxUIMovingGraph(controlWidth, 60, buffer2, 256, 0, 127, "MIDI OUT"));
    
    
    
}

void ControlGUI::addBottomWidgets(){    
    gui->addWidgetRight(new ofxUILabelButton("send", false, dim*4));    
    
}

void ControlGUI::update(){
    //addGraphPoint(control->getValue()); 
    valueIn->addPoint(control->getValue());    
    setValues(control->getValue(), control->getMin(), control->getMax());
    midiOut->addPoint(control->getMIDIvalue());
    midiValue->setLabel(ofToString("midiValue: " + ofToString(control->getMIDIvalue())));
}



void ControlGUI::guiEvent(ofxUIEventArgs &e){
    string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 
    /*
    cout << "name: " + name << endl;
    cout << "kind: " + ofToString(kind) << endl;
    cout << endl;
     */
    
    if(name == "send"){
        control->sendMIDI(); 
    }
    
    else if(name == "CHANNEL"){
        //to do: check if input is number        
        ofxUITextInput *chInput = (ofxUITextInput *) e.widget; 
        string txt = chInput->getTextString();
        if(txt != ""){
           control->channel = ofToInt(chInput->getTextString()); 
        }        
    }
    else if(name == "CC"){
        //to do: check if input is number
        ofxUITextInput *ccInput = (ofxUITextInput *) e.widget; 
        string txt = ccInput->getTextString();
        if(txt != ""){
            control->cc = ofToInt(ccInput->getTextString());
        }
        
    }
    else if(name == "RANGE"){
        ofxUIRangeSlider *rangeSlider = (ofxUIRangeSlider *) e.widget;
        control->outputMin = (int)rangeSlider->getScaledValueLow();
        control->outputMax = (int)rangeSlider->getScaledValueHigh();
    }
    else if(name == "callibrate"){
        ofxUIToggle *c = (ofxUIToggle *) e.widget;
        control->setCallibrating(c->getValue());
    }
    else if(name == "on"){
        ofxUIToggle *c = (ofxUIToggle *) e.widget;
        control->sendMIDIonUpdate = c->getValue();
    }
}

void ControlGUI::setValues(int current, int min, int max){
    currentValue->setLabel("value: " + ofToString(current));
    minValue->setLabel("min: " + ofToString(min));
    maxValue->setLabel("max: " + ofToString(max));
                       
}

void ControlGUI::save(string filename){
    gui->saveSettings(filename);
}

void ControlGUI::loadSettings(string filename){
    gui->loadSettings(filename);   
    //update system values
    // el load tira evento?? en ese caso, está ok. 
}





