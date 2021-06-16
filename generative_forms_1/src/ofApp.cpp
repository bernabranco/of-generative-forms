#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetBackgroundColor(0, 0, 0);
    ofSetBackgroundAuto(true);
    ofEnableAlphaBlending();
    ofEnableAntiAliasing();
    ofSetCircleResolution(200);
    
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    
    audioSetup();

     gui.setup();
     gui.add(radius.setup("radius", 1, 0, 10));
     gui.add(rotatex.setup("rotatex", 0, 0, 5000));
     gui.add(rotatey.setup("rotatey", 0, 0, 5000));
     gui.add(rotatez.setup("rotatez", 50, 0, 100));
     gui.add(points.setup("number of points", 2500, 0, 100000));
     gui.add(amplitudex.setup("amplitudex", 250, 0, 5000));
     gui.add(amplitudey.setup("amplitudey", 250, 0, 5000));
     gui.add(amplitudez.setup("amplitudez", 5, 0, 5000));
     gui.add(anglex.setup("anglex", 0, 0, TWO_PI));
     gui.add(angley.setup("angley", 0, 0, TWO_PI));
     gui.add(anglez.setup("anglez", 0, 0, TWO_PI));
     gui.add(speed.setup("speed", 1, 0, 20));
     gui.add(number.setup("number",10000));
    
     mode=1;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    audioUpdate();
    
    fbo.begin();
    cam.begin();
    ofClear(255,255,255, 0);
    switch(mode){
            
        case 1:
            mode1();
            mode=1;
            break;
            
        case 2:
            mode2();
            mode=2;
            break;
            
        case 3:
            mode3();
            mode=3;
            break;
            
        case 4:
            mode4();
            mode=4;
            break;
            
        case 5:
            mode5();
            mode=5;
            break;
            
        case 6:
            mode6();
            mode=6;
            break;
            
        case 7:
            mode7();
            mode=7;
            break;
            
        case 8:
            mode8();
            mode=8;
            break;
            
        case 9:
            mode9();
            mode=9;
            break;
            
        case 10:
            mode10();
            mode=10;
            break;
            
        case 11:
            mode11();
            mode=11;
            break;
            
        case 12:
            mode12();
            mode=12;
            break;
            
        case 13:
            mode13();
            mode=13;
            break;
    }
    cam.end();
    fbo.end();
   
}

//--------------------------------------------------------------

void ofApp::draw(){
    
    time = ofGetElapsedTimef()*speed;
    
    fbo.draw(0,0);
  
    if(drawgui){
        gui.draw();
    }
}


void ofApp::audioSetup(){
    
    soundStream.printDeviceList();
    
    int bufferSize = 256;
    
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    volHistory.assign(400, 0.0);
    
    bufferCounter    = 0;
    drawCounter        = 0;
    smoothedVol     = 0.0;
    scaledVol        = 0.0;
    
    
    ofSoundStreamSettings settings;
    
    // if you want to set the device id to be different than the default
    // auto devices = soundStream.getDeviceList();
    // settings.device = devices[4];
    
    // you can also get devices for an specific api
    // auto devices = soundStream.getDevicesByApi(ofSoundDevice::Api::PULSE);
    // settings.device = devices[0];
    
    // or get the default device for an specific api:
    // settings.api = ofSoundDevice::Api::PULSE;
    
    // or by name
    auto devices = soundStream.getMatchingDevices("default");
    if(!devices.empty()){
        settings.setInDevice(devices[0]);
    }
    
    settings.setInListener(this);
    settings.sampleRate = 44100;
    settings.numOutputChannels = 0;
    settings.numInputChannels = 2;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);
    
}


void ofApp::audioUpdate(){
    
    //lets scale the vol up to a 0-1 range
    scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
    
    //lets record the volume into an array
    volHistory.push_back( scaledVol );
    
    //if we are bigger the the size we want to record - lets drop the oldest value
    if( volHistory.size() >= 400 ){
        volHistory.erase(volHistory.begin(), volHistory.begin()+1);
    }
}


void ofApp::audioIn(ofSoundBuffer & input){
    
    // samples are "interleaved"
    int numCounted = 0;
    
    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (size_t i = 0; i < input.getNumFrames(); i++){
        left[i] = input[i*2]*0.5;
        right[i] = input[i*2+1]*0.5;
        
        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        numCounted+=2;
    }
    
    //this is how we get the mean of rms :)
    curVol /= (float)numCounted;
    
    // this is how we get the root of rms :)
    curVol = sqrt( curVol );
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
    
    bufferCounter++;
    
}

void ofApp::mode1(){
    
    ofSetColor(255);
    ofFill();
    
    for ( int i = 100; i<points; i++){
        
        float phi= ((pow(5,1/2) + 1) / 2) * i;
        float x = amplitudex*cos(i*anglex+time)*0.0005*i;
        float y = amplitudey*cos(i*angley+time)*0.0005*i;
        float z = amplitudez*sin(i*anglez+time)*0.0005*i;
        
        ofTranslate(x,y,z);
        ofRotateXDeg(rotatex);
        ofRotateYDeg(rotatey);
        ofRotateZDeg(number);
    
        ofDrawSphere(x,y,z, radius*sin(0.02*i+time));
     }
}

void ofApp::mode2(){
    
    ofSetColor(255);
    ofFill();

    for ( int i = 0; i<points; i++){
        
        float phi= ((pow(5,1/2) + 1) / 2) * i;
        
        float x = 50*cos(i*0.01+time*2)*0.0001*i;
        float y = -ofGetHeight()+i/2;
        float z = 50*sin(i*0.01+time*2)*0.0001*i;
        
        ofTranslate(0,0);
       ofRotateXDeg(rotatex);
            ofRotateYDeg(rotatey);
        ofRotateZDeg(rotatez);
        ofDrawSphere(ofGetWidth()*0.5+x,y,z, radius + 5+5*sin(0.02*i+time));
    }
}


void ofApp::mode3(){
    
    ofSetColor(255);
    ofFill();

    for ( int i = 0; i<points; i++){
        
        float phi= ((pow(5,1/2) + 1) / 2) * i;
        
        float x = 250*cos(i*0.005+time)*0.0005*i;
        float y = 250*sin(i*0.005+time)*0.0005*i;
        float z = 250*sin(i*0.005+time)*0.0005*i;
        
        ofTranslate(0,0);
        ofRotateXDeg(rotatex);
            ofRotateYDeg(rotatey);
        ofRotateZDeg(rotatez+number);
        ofDrawSphere(ofGetWidth()*0.5+x,y,z, radius + 5*sin(0.02*i+time));
    }
}


void ofApp::mode4(){
    
    ofSetColor(255);
    ofFill();

    for ( int i = 0; i<points; i++){
        
        float phi= ((pow(5,1/2) + 1) / 2) * i;
        
        float x = amplitudex*cos(i*0.001618+time);
        float y = amplitudey*cos(i*0.001618+time);
        float z = amplitudez*sin(i*0.001618+time);
        
        ofTranslate(0,0);
        ofRotateXDeg(rotatex);
            ofRotateYDeg(rotatey);
        ofRotateZDeg(rotatez);
        ofDrawSphere(ofGetWidth()*0.5+x,y,z, radius + 5*sin(0.02*i+time));
        
    }
}


void ofApp::mode5(){
    
    ofSetColor(255);
    ofFill();

    for ( int i = 0; i<points; i++){
        
        float phi= ((pow(5,1/2) + 1) / 2) * i;
        
        float x = 250*cos(i*0.001+time)*0.0005*i;
        float y = 250*sin(i*0.001+time)*0.0005*i;
        float z = 250*sin(i*0.001+time)*0.0005*i;
        
        ofTranslate(0,0);
        ofRotateXDeg(rotatex);
            ofRotateYDeg(rotatey);
        ofRotateZDeg(rotatez);
        ofDrawSphere(ofGetWidth()*0.5+x,y,z, radius + 5*sin(0.02*i+time));
    }
}


void ofApp::mode6(){
    
    ofSetColor(255);
    ofFill();

    for ( int i = 0; i<points; i++){
        
        float phi= ((pow(5,1/2) + 1) / 2) * i;
        
        float x = 250*cos(i*0.75+time)*0.0005*i;
        float y = 250*sin(i*0.95+time)*0.0005*i;
        float z = 250*sin(i*0.65+time)*0.0005*i;
        
        ofTranslate(0,0);
        ofRotateXDeg(rotatex);
            ofRotateYDeg(rotatey);
        ofRotateZDeg(rotatez);
        ofDrawSphere(ofGetWidth()*0.5+x,y,z, radius + 5*sin(0.02*i+time));
        
    }
}


void ofApp::mode7(){
    
    ofSetColor(255);
    ofFill();

    for ( int i = 0; i<points; i++){
        
        float phi= ((pow(5,1/2) + 1) / 2) * i;
        
        float x = 250*cos(i*0.01+time*3)*0.0005*i;
        float y = -ofGetHeight()+250*sin(i*0.01+time*2)*0.0005*i;
        float z = 250*sin(i*0.01+time*2)*0.0005*i;
        
        ofTranslate(0,0);
        ofRotateXDeg(rotatex);
            ofRotateYDeg(rotatey);
        ofRotateZDeg(rotatez);
        ofDrawSphere(ofGetWidth()*0.5+x,y,z, radius + 5*sin(0.02*i+time));
    }
}


void ofApp::mode8(){
    
    ofSetColor(255);
    ofFill();

    for ( int i = 0; i<points; i++){
        
        float phi= ((pow(5,1/2) + 1) / 2) * i;
        
        
        float x = 250*cos(i*0.01+time)*0.001*i;
        float y = -ofGetHeight()+250*sin(i*0.01+time)*0.001*i;
        float z = 250*sin(i*0.01+time)*0.001*i;
        
        ofTranslate(0,0);
        ofRotateXDeg(rotatex);
            ofRotateYDeg(rotatey);
        ofRotateZDeg(rotatez);
        ofDrawSphere(ofGetWidth()*0.5+x,y,z, radius + 5*sin(0.02*i+time));
    }
}


void ofApp::mode9(){
    
    ofSetColor(255);
    ofFill();

    for ( int i = 0; i<points; i++){
        
        float phi= ((pow(5,1/2) + 1) / 2) * i;
        
        float x = 250*cos(i*0.001+time)*0.0005*i;
        float y = -ofGetHeight()+250*sin(i*0.001+time)*0.0005*i;
        float z = 250*sin(i*0.001+time)*0.0005*i;
        
        ofTranslate(0,0);
        ofRotateXDeg(rotatex);
            ofRotateYDeg(rotatey);
        ofRotateZDeg(rotatez);
        ofDrawSphere(ofGetWidth()*0.5+x,y,z, radius + 5*sin(0.02*i+time));
    }
}


void ofApp::mode10(){
    
    ofSetColor(255);
    ofFill();

    for ( int i = 0; i<points; i++){
        
        float phi= ((pow(5,1/2) + 1) / 2) * i;
        
        
        float x = 150*cos(i*0.01+time)*0.001*i;
        float y = -ofGetHeight()+i/2;
        float z = 150*sin(i*0.01+time)*0.001*i;
        
        ofTranslate(0,0);
      ofRotateXDeg(rotatex);
            ofRotateYDeg(rotatey);
        ofRotateZDeg(rotatez);
        ofDrawSphere(ofGetWidth()*0.5+x,y,z, radius + 5*sin(0.02*i+time));
    }
}


void ofApp::mode11(){
    
    ofSetColor(255);
    ofFill();

    for ( int i = 0; i<points; i++){
        
        float phi= ((pow(5,1/2) + 1) / 2) * i;
        
        float x = amplitudex*cos(i*anglex+time)*0.001*i;
        float y = -ofGetHeight() + amplitudey;
        float z = amplitudez*sin(i*anglez+time)*0.001*i;
        
        ofTranslate(0,0);
        ofRotateXDeg(rotatex);
            ofRotateYDeg(rotatey);
        ofRotateZDeg(rotatez);
        ofDrawSphere(ofGetWidth()*0.5+x,y,z, radius + 5*sin(0.02*i+time));
    }
}


void ofApp::mode12(){
    
    ofSetColor(255);
    ofFill();
    
    for ( int i = 0; i<points; i++){
        
        float phi= ((pow(5,1/2) + 1) / 2) * i;
        
        float x = amplitudex*cos(i*anglex+time)*0.001*i;
        float y = -ofGetHeight();
        float z = amplitudez*sin(i*anglez+time)*0.001*i;
        
        ofTranslate(anglex,angley,anglez);
        ofRotateXDeg(rotatex);
            ofRotateYDeg(rotatey);
        ofRotateZDeg(rotatez);
        ofDrawSphere(ofGetWidth()*0.5+x,y,z, radius + 5*sin(0.02*i+time));
    }
}


void ofApp::mode13(){
    
    ofSetColor(255);
    ofFill();

    for ( int i = 0; i<points; i++){
        
        float phi= ((pow(5,1/2) + 1) / 2) * i;
        
        float x = 75*cos(i*0.01+time)*0.001*i;
        float y = -ofGetHeight();
        float z = 75*sin(i*0.01+time)*0.001*i;
        
        ofTranslate(0,0);
        ofRotateXDeg(rotatex);
        ofRotateYDeg(rotatey);
        ofRotateZDeg(rotatez);
        ofDrawSphere(ofGetWidth()*0.5+x,y,z, radius + 5*sin(0.02*i+time));
    }
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch(key){
            
        case '1':
            mode = 1;
            break;
            
        case '2':
            mode = 2;
            break;
            
        case '3':
            mode = 3;
            break;
            
            
        case '4':
            mode = 4;
            break;
            
        case '5':
            mode = 5;
            break;
            
        case '6':
            mode = 6;
            break;
            
        case '7':
            mode = 7;
            break;
            
        case '8':
            mode = 8;
            break;
            
        case '9':
            mode = 9;
            break;
            
        case '0':
            mode = 10;
            break;
            
        case 'q':
            mode = 11;
            break;
            
        case 'w':
            mode = 12;
            break;
            
        case 'e':
            mode = 13;
            break;
            
        case 'z':
            if (drawgui){
                drawgui=false;
            } else {
                drawgui=true;
            }
            break;
            
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}


//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
