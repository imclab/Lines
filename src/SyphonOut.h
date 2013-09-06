//
//  SyphonOut.h
//  firmataExample
//
//  Created by luisaph on 11/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef firmataExample_SyphonOut_h
#define firmataExample_SyphonOut_h
#include "ofMain.h"
#include "ofxSyphon.h"

class SyphonOut{    
public:
    void setup(int width, int height);
    void draw();
private:    
    ofTexture tex;   
	ofxSyphonServer mainOutputSyphonServer;
	ofxSyphonServer individualTextureSyphonServer;	
	ofxSyphonClient mClient;
};

#endif
