#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    currentProgram = 0; 

	ofSetVerticalSync(true);
	ofSetFrameRate(60);
    ofSetLogLevel(OF_LOG_SILENT);
    ofSetBackgroundColor(0);
        
    system.setup();    
    syphon.setup(ofGetWindowWidth(), ofGetWindowHeight());
    setupGUI(); 
    
}

void testApp::update(){
    system.update();        
    updateGUI();    
}

void testApp::draw(){    
	system.draw();
    syphon.draw();    
    /*anything drawn here will not go to Syphon*/
}

void testApp::exit()
{
    system.close();
    for(int i = 0; i < system.getNumControllers(); i++){        
        delete controlGUIs[i];
    }
    delete gui;     
    
}

void testApp::setupGUI(){
    
    float dim = 16; 
	float spacing = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float controlLength = 255 - spacing*2; 
    int panelWidth = 255 + spacing*2;
    
    gui = new ofxUICanvas(0,0,ofGetWindowWidth(), ofGetWindowHeight());    
    gui->setColorBack(ofColor(100,70));
    
    
    arduinoOn = new ofxUIToggle("arduino in", false, dim, dim);      
    gui->addWidgetDown(arduinoOn);
    
    midiOn = new ofxUIToggle("midi out", false, dim, dim, OFX_UI_FONT_MEDIUM); 
    gui->addWidgetRight(midiOn); 
    
    currentFile = new ofxUILabel("current file: ", OFX_UI_FONT_SMALL);
    gui->addWidgetDown(currentFile);
    
    //vector<string> items; 
    //programs = (ofxUIDropDownList *) gui->addDropDownList("program", items, controlLength);
    //add label with current fileName.    
    gui->addLabelButton("load file", false, controlLength/2);
    fileNameLoad = new ofxUITextInput("FILENAME_LOAD", "", controlLength/2);
    gui->addWidgetRight(fileNameLoad);
    
    gui->addLabelButton("save as", false, controlLength/4*2);  
    fileNameSave = new ofxUITextInput("FILENAME_SAVE", "1", controlLength/2);
    gui->addWidgetRight(fileNameSave);
    
    
	callibrate = new ofxUIToggle( "callibrate", system.callibrating, dim, dim);      
    gui->addWidgetDown(callibrate); 
    
    smoothInput = new ofxUIToggle( "smooth input", system.smoothInput, dim, dim);      
    gui->addWidgetDown(smoothInput); 
    
    gui->addToggle( "send MIDI", true, dim, dim); 
    
    vector<string> names; 
    names.push_back("values");
    names.push_back("tempo");  
    names.push_back("waves");  
    gui->addRadio("visuals", names, OFX_UI_ORIENTATION_VERTICAL, dim, dim);
    
    int cols = 4;
    int rows = 2; 
    
    int panelHeight = 400;
    for(int i = 0; i < system.getNumControllers(); i++){   
        int col = i %cols + 1;
        int row = i/cols;
        string type = system.controllers[i]->getType();
        if(type == "Key"){
             controlGUIs.push_back(new KeyGUI(i, panelWidth, (panelWidth + dim)*(col), panelHeight*(row)));
        }
        else if(type == "Pot"){
            controlGUIs.push_back(new PotGUI(i, panelWidth, (panelWidth + dim)*(col), panelHeight*(row)));
        }
        else if(type == "Switch"){
            //controlGUIs.push_back(new SwitchGUI(i, panelWidth, (panelWidth + dim)*(col), panelHeight*(row)));
        }
        controlGUIs[i]->control = system.controllers[i]; 
        controlGUIs[i]->setup();
        ofAddListener(controlGUIs[i]->gui->newGUIEvent, controlGUIs[i], &ControlGUI::guiEvent);                
    }
    
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
    loadSettings();     
    
}

void testApp::updateGUI(){
    
    //arduinoStatus->setLabel(input.getStatus());
    arduinoOn->setValue(system.input.connected);   
    callibrate->setValue(system.callibrating);
    for(int i = 0; i < system.getNumControllers(); i++){
        controlGUIs[i]->update();
        
        /*
        controlGUIs[i]->addGraphPoint(system.controllers[i]->getValue());      
        controlGUIs[i]->setValues(system.controllers[i]->getValue(), system.controllers[i]->getMin(), system.controllers[i]->getMax()); 
         */
    }
    
}

void testApp::guiEvent(ofxUIEventArgs &e){
    string name = e.widget->getName(); 
	int kind = e.widget->getKind();
    
    if(name == "save as"){
        saveSettings();
    }
    else if(name == "load file"){
        loadInputSettings(fileNameLoad->getTextString());        
        
    }
    else if(name == "callibrate"){        
        ofxUIToggle *t = (ofxUIToggle * )e.widget;
        system.setCallibrate(t->getValue());
        for(int i = 0; i < system.getNumControllers(); i++){
            controlGUIs[i]->callibrate->setValue(t->getValue());
        }
        
    }
    else if(name == "smooth input"){
        ofxUIToggle *t = (ofxUIToggle * )e.widget;
        system.smoothInput = t->getValue();
    }
    else if(name == "program")
    {
        /*DROPDOWN DOESN'T SAVE ITS LIST OF ITEMS (would have to implement myself)
        ofxUIDropDownList *ddlist = (ofxUIDropDownList *) e.widget;
        vector<ofxUIWidget *> &selected = ddlist->getSelected(); 
        for(int i = 0; i < selected.size(); i++)
        {
            cout << "SELECTED: " << selected[i]->getName() << endl; 
        }
         */
    }
    else if(name == "send MIDI"){
        ofxUIToggle *t = (ofxUIToggle * )e.widget;
        system.setSendMIDI(t->getValue());
        
    }
    else if(name =="tempo"){
        system.setDrawMode(TEMPO);
    }
    else if(name =="waves"){
        system.setDrawMode(WAVES);
    }
    else if(name == "values"){
        system.setDrawMode(VALUES);
    }
    
    
}

void testApp::keyPressed  (int key){
    switch (key) {
            
        case 'q':
            //exit();
            break;
        case 's':
            saveSettings();
            break;
        case 'c':
            //system.setCallibrate();
            break;
        case 'h':
            gui->toggleVisible();
            for(int i = 0; i < system.getNumControllers(); i++){
                controlGUIs[i]->gui->toggleVisible();
            }
            break;
        case 'a':
            system.toggleUseArduinoInput();
    }
}

void testApp::mouseReleased(int x, int y, int button){
    //MidiOut::getInstance().sendControlChange(10, 10, 100);
        //cout << "mouseReleased" << endl;
}



void testApp::loadSettings(){  
    string filename = fileNameLoad->getTextString();
    gui->loadSettings("GUI/guiSettings.xml"); 
    if(filename == "") filename = fileNameSave->getTextString(); //load last saved settings.
    loadInputSettings(filename);
    
}

void testApp::loadInputSettings(string filename){    
    
    for(int i = 0; i < system.getNumControllers(); i++){
        controlGUIs[i]->loadSettings("GUI/" + filename + "_input_" + ofToString(i) + ".xml"); 
    } 
    currentFile->setLabel("current files: " + filename + "_input_i.xml");
}

void testApp::saveSettings(){
    gui->saveSettings("GUI/guiSettings.xml");
    string filename = fileNameSave->getTextString();
    for(int i = 0; i < system.getNumControllers(); i++){        
        controlGUIs[i]->save("GUI/" + filename + "_input_" + ofToString(i) + ".xml");        
    }
    currentFile->setLabel("current files: " + filename + "_input_i.xml");
    //programs->addToggle(fileName->getTextString());
    
}




