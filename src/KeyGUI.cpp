//
//  KeyGUI.cpp
//  firmataExample
//
//  Created by luisaph on 11/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "KeyGUI.h"

KeyGUI::KeyGUI(int _id, int _width, int _xPos, int _yPos)
:ControlGUI(_id, _width, _xPos, _yPos){
    
    
}

void KeyGUI::addControlSpecificWidgets(){  
    gui->addWidgetDown(new ofxUILabel("CH", OFX_UI_FONT_SMALL));
    gui->addWidgetRight(new ofxUITextInput("CHANNEL", "1", dim*2));//->setAutoClear(true) 
    gui->addWidgetRight(new ofxUITextInput("notePos", "0", dim*2));     
    gui->addWidgetDown(new ofxUISlider("threshold", 0, 300, 60, dim*10, 10));
    
}

