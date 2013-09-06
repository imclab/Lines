//
//  KeyGUI.h
//  firmataExample
//
//  Created by luisaph on 11/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef firmataExample_KeyGUI_h
#define firmataExample_KeyGUI_h
#include "ControlGUI.h"

class KeyGUI: public ControlGUI{
public:
    KeyGUI();
    ~KeyGUI();
    KeyGUI(int _id, int _width, int _xPos, int _yPos);
    void addControlSpecificWidgets();
};

#endif
