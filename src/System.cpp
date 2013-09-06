//
//  System.cpp
//  firmataExample
//
//  Created by luisaph on 11/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "System.h"

System::System(){
    
}

System::~System(){
    for(int i = 0; i < getNumControllers(); i++){
        delete controllers[i];
    }
    
}

void System::setup(){
    useArduinoInput = false;
    numControllers = 8;
    smoothInput = true;
    drawMode = VALUES;    
    callibrating = false;
    sendMIDI = false;    
    lastDraw = ofGetElapsedTimeMillis();
     
    for(int i = 0; i < getNumControllers(); i++){ //one volume, one note.
        MIDIControl *volume = new Key(i, "" + i);     
        controllers.push_back(volume);    
    }  
    
    for(int i = 0; i < controllers.size(); i++){
        MIDIControl *control = controllers[i];               
        control->setCallibrating(callibrating);
        control->sendMIDIonUpdate = sendMIDI;        
    }
    
    input = Input(controllers.size());
    input.connect(); 
     
}

int System::getNumControllers(){
    return numControllers;
}

void System::setSendMIDI(bool value){
    sendMIDI = value;
    for(int i = 0; i < controllers.size(); i++){
        controllers[i]->sendMIDIonUpdate = sendMIDI;
    }
}

void System::update(){
    input.update();
    for(int i = 0; i < controllers.size(); i++){
        if(useArduinoInput){
            if(input.connected){           
               controllers[i]->setValue(input.getValue(i, smoothInput)); 
            }
       }    
        else{        
            int testValue = (int)(ofNoise(ofGetElapsedTimeMillis()/1000, 1) * 80);
            controllers[i]->setValue(testValue);
        }
        
        controllers[i]->update(); 
    }
    
}

void System::draw(){   
    
    ofSetColor(0,0,0);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    switch(drawMode){
        case VALUES:
            drawValues();            
            break;
        case TEMPO:
            drawTempo();
            break;
        case WAVES: 
            drawWaves();
            break;
    }
    
}

void System::drawValues(){
    ofSetBackgroundColor(0, 0, 0);
    for(int i = 0; i < controllers.size(); i++){
        controllers[i]->draw();
    } 
}

void System::drawTempo(){
    /*
    int currentMIDItempo = tempo->getMIDIvalue();    
    int currentBPMtempo = ofMap(currentMIDItempo, tempo->outputMin, tempo->outputMax, 20, 120   ); //TO DO: hack. should not be hardcoded. it's the limits to tempo i've set in Live. Actually, shouldn't set limits there but HERE (and know equivalency to BPM). 
    int millisPM = currentBPMtempo * 1000 / 60;
    int currentTime = ofGetElapsedTimeMillis();
    
    //FLASHING SQUARE 
    if(currentTime - lastDraw > millisPM){
        ofSetColor(255);
        ofRect(0, 0, ofGetWidth(), ofGetHeight()/10);
        lastDraw = currentTime;
    }
    //BPM LINES
    int numLines = currentBPMtempo / 10;
    int separation = ofGetWidth() / numLines;
    for(int i = 0; i < ofGetWidth(); i+= separation){
        ofRect(i, 0, 2, ofGetHeight());
    }
     */
    

}

void System::drawWaves(){
    //int curvyness = timbre->getMIDIvalue(); //or volume of piano
    //draw sinewave with #of points depending on curvyness
    //int separation = ofGetWidth() / curvyness;
    
}

void System::setCallibrate(bool value){
    callibrating = value;    
    for(int i = 0; i < controllers.size(); i++){
        controllers[i]->setCallibrating(callibrating);        
    }
    
}

void System::toggleUseArduinoInput(){
    useArduinoInput = !useArduinoInput;
}

void System::setDrawMode(DrawMode mode){
    drawMode = mode;
}

void System::close(){
    input.disconnect();
    //MidiOut::getInstance().close();  
    
}