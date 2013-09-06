//
//  PotGUI.cpp
//  firmataExample
//
//  Created by luisaph on 11/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "PotGUI.h"

PotGUI::PotGUI(int _id, int _width, int _xPos, int _yPos)
:ControlGUI(_id, _width, _xPos, _yPos){
    
}



void PotGUI::addControlSpecificWidgets(){    
    gui->addRangeSlider("RANGE", 0.0, 127.0, 50.0, 100.0, controlWidth, dim);
    gui->addWidgetDown(new ofxUILabel("CH", OFX_UI_FONT_SMALL));
    gui->addWidgetRight(new ofxUITextInput("CHANNEL", "1", dim*2));//->setAutoClear(true)
    gui->addWidgetRight(new ofxUILabel("CC", OFX_UI_FONT_SMALL));
    gui->addWidgetRight(new ofxUITextInput("CC", "1", dim*2)); //->setAutoClear(true)    
    
    
}



