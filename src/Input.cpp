//
//  Input.cpp
//  firmataExample
//
//  Created by luisaph on 11/19/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Input.h"

Input::Input(){    
	Input(1);
}

Input::Input(int num){
    bSetupArduino	= false;
    connected = false;
    status = "arduino not ready...\n";
    numHistoricalValues = 5;
    setNumInputs(num);
    
}

void Input::connect(){
    
    //if(ard.connect("/dev/tty.usbserial-A800evn7", 57600)){
    if(ard.connect("/dev/tty.usbmodemfa141", 57600)){ //arduino mega
        connected = true;
    }    
	ofAddListener(ard.EInitialized, this, &Input::setupArduino);
     
}

void Input::setNumInputs(int num){
    numInputs = num;
    for(int i = 0; i < numInputs; i++){
        vector<int> row(numHistoricalValues, 0);
        /*for(int j = 0; j < numHistoricalValues; i++){
           row.push_back(0);
        }*/
        values.push_back(row);
        /*
        cout << "[0][0]: " << values[0][0];
        cout << "[0][1]: " << values[0][1];
        cout << "[0][2]: " << values[0][2];
        cout << "[0][3]: " << values[0][3];
        cout << "[0][4]: " << values[0][4];
        cout << "[1][0]: " << values[0][0];
        cout << "[2][1]: " << values[0][1];
        cout << "[3][2]: " << values[0][2];*/
        
    }
}

void Input::update(){    
    
	updateArduino();
}

string Input::getStatus(){    
    return status;
}

int Input::getValue(int pos, bool smooth){
    int val = 0;
    if(pos < values.size()){
        if(smooth){ //simple average
            int total = 0; 
            for(int i = 0; i < numHistoricalValues; i++){
                total += values[pos][i];
            }
            val = total / numHistoricalValues;
        }
        else{
            val = values[pos][0];
        }
        
    }
    return val;
}

void Input::setupArduino(const int & version) {
	
	ofRemoveListener(ard.EInitialized, this, &Input::setupArduino);
    bSetupArduino = true;
    status = "connected... no values yet.";
    cout << ard.getFirmwareName() << endl; 
    cout << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion() << endl;
    ard.sendAnalogPinReporting(0, ARD_ANALOG);
    //ard.sendAnalogPinReporting(2, ARD_ANALOG);
    ofAddListener(ard.EAnalogPinChanged, this, &Input::analogPinChanged);
    
    ard.sendDigitalPinMode(1, ARD_INPUT);
    ofAddListener(ard.EDigitalPinChanged, this, &Input::digitalPinChanged);
     
}


void Input::updateArduino(){    
    
	ard.update();    
    
}

void Input::analogPinChanged(const int & pinNum) {
    status = "analog pin: " + ofToString(pinNum) + " = " + ofToString(ard.getAnalog(pinNum));
    if(pinNum < numInputs){        
        for(int i = numHistoricalValues - 1; i > 0; i--){ //shift historical values
            values[pinNum][i] = values[pinNum][i-1];
        }
        values[pinNum][0] = ard.getAnalog(pinNum);
    }
     
}

void Input::digitalPinChanged(const int & pinNum) {
    
    buttonState = ard.getDigital(pinNum);
    
    
}

void Input::disconnect(){
    ard.disconnect();
}