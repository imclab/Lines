//
//  Input.h
//  firmataExample
//
//  Created by luisaph on 11/19/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ofMain.h"

#ifndef firmataExample_Input_h
#define firmataExample_Input_h

class Input{
public:    
    Input();
    Input(int numInputs);
    void connect();
    void disconnect();
    bool connected;
    void setNumInputs(int num);
    void update();
    int getValue(int pos, bool smooth);
    std::string  getStatus();
    
    int buttonState; 
    
private:
    ofArduino ard;   
    int numInputs;
    int numHistoricalValues;
	bool bSetupArduino;
    
    
    std::string status;
    vector< vector <int> > values; //last 5 values for each input. //TO DO: this is a bit cryptic.
    
    
    void setupArduino(const int & version);
    void digitalPinChanged(const int & pinNum);
    void analogPinChanged(const int & pinNum);
	void updateArduino();
    
    
    

};

#endif
