//
//  dpHakoniwaMagnetPendulum.h
//  example-ramMotionExtractor
//
//  Created by itotaka on 1/16/15.
//
//

#ifndef __example_ramMotionExtractor__dpHakoniwaMagnetPendulum__
#define __example_ramMotionExtractor__dpHakoniwaMagnetPendulum__

#define NMAGNETS 2

#include "ramMain.h"
#include "ramMotionExtractor.h"
using namespace rdtk;
class dpHakoniwaMagnetPendulum : public BaseScene {
    
public:
    
    string getName() const {return "dpHMagPendulum";};
    
    void setupControlPanel();
    void setup();
    void sendOsc();
    void update();
    void draw();
    void drawActor(const Actor& actor);
    void guiEvent(ofxUIEventArgs &e);
    void onEnabled();
    void onDisabled();
    
private:
    
	float mDistanceThreshold;
    bool bOn[NMAGNETS];
    
    MotionExtractor	mMotionExtractor;
    ofxOscSender mSenderOnOff;

    static const ofColor MAIN_COLOR;
    
};


#endif /* defined(__example_ramMotionExtractor__dpHakoniwaMagnetPendulum__) */
