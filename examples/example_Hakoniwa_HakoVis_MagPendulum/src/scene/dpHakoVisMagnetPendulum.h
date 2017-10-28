//
//  doHakoVisRecordGrid.h
//  RAMDanceToolkit
//
//  Created by kezzardrix2 on 2015/01/10.
//
//

#ifndef RAMDanceToolkit_doHakoVisRecordGrid_h
#define RAMDanceToolkit_doHakoVisRecordGrid_h

#include "dpRecordBufferCircle.h"
using namespace rdtk;
class dpHakoVisMagnetPendulum : public BaseScene{
public:
    
    string getName() const{return "dpVisMagPendulum";}
    
    void setupControlPanel();
    void setup();
    void record(ofPoint pt);
    void changeRecordTarget();
    void receiveOsc();
    void update();
    void draw();
    void onEnabled();
    
private:
 
    vector<dpRecordBufferCircle>mCircles;
    
    static const int DIV_X = 3;
    static const int DIV_Y = 2;
    static const int SPACE = 250;
    
	int mRecordTargetNum;
	int mBeginFrame;
    
	float mScale;
    
    ofVec2f mPos;
    
    OscReceiveTag mReceiver;
    
};

#endif
