#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#include "System.h"
#include "ofxUI.h"
#include "ControlGUI.h"
#include "PotGUI.h"
#include "KeyGUI.h"
#include "SyphonOut.h"


class testApp : public ofSimpleApp{

public:
    void setup();
	void update();    
	void draw();
    void exit();
    void keyPressed(int key);
    void mouseReleased(int x, int y, int button);
    void guiEvent(ofxUIEventArgs &e);
    
private:
    void setupGUI();
    void updateGUI();
    
    void save();
    void saveSettings();
    void loadSettings();
    void loadInputSettings(string filename);	
    
    System      system;
    SyphonOut syphon; 
    
    int currentProgram;
    vector<ControlGUI *> controlGUIs;  
    ofxUICanvas *gui;
    
    ofxUIToggle *arduinoOn;
    ofxUIToggle *midiOn;
    ofxUILabel *currentFile;
    
    ofxUITextInput *fileNameLoad;
    ofxUITextInput *fileNameSave;
    
    ofxUIToggle *callibrate;
    ofxUIToggle *smoothInput;
    //ofxUIDropDownList *programs; //TO DO: scan folder for saved programs. Problem: dropdown list doesn't really behave as a dropdown list.
    
    
     
    
      
    
    
    
    
    

};

