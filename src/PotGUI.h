//
//  PotGUI.h
//  firmataExample
//
//  Created by luisaph on 11/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef firmataExample_PotGUI_h
#define firmataExample_PotGUI_h
#include "ControlGUI.h"
#include "Pot.h"

class PotGUI: public ControlGUI{
public:
    PotGUI(); 
    PotGUI(int _id, int _width, int _xPos, int _yPos);    
    void addControlSpecificWidgets();
    
    
};


#endif
