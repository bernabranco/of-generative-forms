#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxShader.h"


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void audioIn(ofSoundBuffer & input);
    void audioSetup();
    void audioUpdate();
    
    vector <float> left;
    vector <float> right;
    vector <float> volHistory;
    
    int     bufferCounter;
    int     drawCounter;
    
    float smoothedVol;
    float scaledVol;
    
    float curVol = 0.0;
    
    ofSoundStream soundStream;
    
    int mode;
    float time;
    
    void mode1();
    void mode2();
    void mode3();
    void mode4();
    void mode5();
    void mode6();
    void mode7();
    void mode8();
    void mode9();
    void mode10();
    void mode11();
    void mode12();
    void mode13();
    
    bool z = false;
    
    ofEasyCam cam;
    ofFbo fbo;
    ofxFloatSlider radius;
    ofxFloatSlider radius_variation;
    ofxFloatSlider rotatex;
    ofxFloatSlider rotatey;
    ofxFloatSlider rotatez;
    ofxFloatSlider points;
    ofxFloatSlider amplitudex;
    ofxFloatSlider amplitudey;
    ofxFloatSlider amplitudez;
    ofxFloatSlider anglex;
    ofxFloatSlider angley;
    ofxFloatSlider anglez;
    ofxFloatSlider speed;
    ofxFloatSlider toggle;
    ofxFloatField  number;
    
    ofxPanel gui;
    bool drawgui=true;
    
};
