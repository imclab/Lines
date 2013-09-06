//
//  SyphonOut.cpp
//  firmataExample
//
//  Created by luisaph on 11/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "SyphonOut.h"

/*SyphonOut::SyphonOut(){
    
}*/

void SyphonOut::setup(int width, int height){
    mainOutputSyphonServer.setName("Screen Output");
	individualTextureSyphonServer.setName("Texture Output");
    
	mClient.setup();
    
    mClient.setApplicationName("Simple Server");
    mClient.setServerName("");
	
    tex.allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGBA); 
}

void SyphonOut::draw    (){    
    mClient.draw(50, 50);    
    
	mainOutputSyphonServer.publishScreen();
    
    individualTextureSyphonServer.publishTexture(&tex);
}