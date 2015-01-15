//
//  HakoniwaStruggle.h
//  RAMDanceToolkit
//
//  Created by kezzardrix2 on 2015/01/07.
//
//

#ifndef RAMDanceToolkit_HakoniwaStruggle_h
#define RAMDanceToolkit_HakoniwaStruggle_h

#define STRINGIFY(A) #A

class dpHakoniwaStruggle : public ramBaseScene{
public:
    string getName() const { return "dpHakoniwaStruggle"; }
    
	void setupControlPanel(){
        ramGetGUI().addToggle("dir", &mMotorDir);
        ramGetGUI().addToggle("vibeAuto", &isVibeAuto);
        ramGetGUI().addToggle("vibeWhenMoveFast", &isVibeWhenActorMoveFast);
        ramGetGUI().addSlider("strength", 0.0, 255.0, &mVibeStrength);
        ramGetGUI().addSlider("thresh", 0.0, 30.0, &mVibeThresh);
        ramGetGUI().addButton("vibe");
        ramGetGUI().addSlider("timeSpan", 0.01, 3.0, &mVibeTimeSpan);
        ramGetGUI().addSlider("tempo",2,8.0,&mVibeTempo);
        ramGetGUI().addSlider("dur",0.1,2.0,&mVibeDur);
        ramGetGUI().addToggle("isDrawActor", &isDrawActor);
        ramGetGUI().addToggle("isDrawFloor", &isDrawFloor);
        ramGetGUI().addSlider("lineWidth",1.0,20.0,&mLineWidth);
        
        ofxUIRadio *radio = NULL;
        
        const float dim = 16.0f;
        
        ofxUICanvas* panel = ramGetGUI().getCurrentUIContext();
        
        vector<string> names;
        
        names.push_back("JOINT_ABDOMEN");
        names.push_back("LEFT_WRIST");
        names.push_back("RIGHT_WRIST");
        names.push_back("LEFT_ANKLE");
        names.push_back("RIGHT_ANKLE");
        
        radio = new ofxUIRadio("JOINT", names, OFX_UI_ORIENTATION_VERTICAL, dim, dim);
        //radio->getToggles().at(ramActor::JOINT_LEFT_HAND)->setValue(true);
        panel->addWidgetDown(radio);
        
        ofAddListener(ramGetGUI().getCurrentUIContext()->newGUIEvent, this, &dpHakoniwaStruggle::onPanelChanged);
    }
    void setup(){
        mSender.setup("192.168.20.53",8528);
        // ofAddListener(ReachAtStruggleEvent::events, this, &HakoniwaStruggle::reachEvent);
        
        mVibe.speed = 0.666;
        
        mPlane.setResolution(14, 14);
        
        mVert = STRINGIFY(uniform  float   val;
                          uniform  float time;
                          
                          float rand(vec2 co){
                              return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453) * 2.0 - 1.0;
                          }
                          
                          void main(){
                              vec4 newVertex = gl_Vertex;
                              newVertex.x += rand(newVertex.xy + vec2(time)) * val;
                              newVertex.y += rand(newVertex.xx + vec2(time)) * val;
                              newVertex.z += rand(newVertex.yx + vec2(time)) * val;
                              gl_Position = gl_ModelViewProjectionMatrix * newVertex;
                              gl_FrontColor = gl_Color;
                          }
                          
                          );
        
        mFrag = STRINGIFY(
                          void main(){
                              gl_FragColor = gl_Color;
                          }
                          );
        
        mDisplace.setupShaderFromSource(GL_VERTEX_SHADER, mVert);
        mDisplace.setupShaderFromSource(GL_FRAGMENT_SHADER, mFrag);
        mDisplace.linkProgram();
        
    }
    
    void vibe(){
        //mVibe.speed = mVibeDur;
        mVibe.imSet((int)mVibeStrength);
        
        
        //mMotorDir = !mMotorDir;
        //mMotorDir %= 2;//(int)ofRandom(0,2);
    }
    
    void stopVibe(){
        mVibe.set(0);
    }
    
   
    void update(){
        ramSetViewPort(dpGetFirstScreenViewPort());
        
        ofSetLineWidth(mLineWidth);
        
        if(isVibeWhenActorMoveFast == false && isVibeAuto == false)mVibeFromActor.imSet(mVibeStrength);
        
        vibeAuto();
        
        int numActor = getNumNodeArray();
        
        for(int i = 0; i < numActor; i++){
            const ramNodeArray &array = getNodeArray(i);
            
            for(int j = 0; j < array.getNumNode(); j++){
                const ramNode node = array.getNode(j);
                
                
                if(j == mJointNum){
                    if(node.getVelocity().length() > mVibeThresh){
                        
                        if(isVibeWhenActorMoveFast){
                            
                            mVibeFromActor.imSet(mVibeStrength);
                            mVibeFromActor.set(0);
                            
                        }else{
                            mVibeFromActor.imSet(0);
                            mVibe.imSet(0);
                        }
                    }
                }
            }
        }
        
        float vibeVal = mVibe.val + mVibeFromActor.val;
        
        if(vibeVal > 255.0)vibeVal = 255.0;
        
        mSmoothedVibeVal.set(vibeVal);
        
        sendOsc(vibeVal);
        
        mVibe.update();
        mVibeFromActor.update();
        mSmoothedVibeVal.update();
        
    }
    
    void sendOsc(float vibeVal){
        ofxOscMessage m;
        m.setAddress("/dp/hakoniwa/struggle");
        if(mMotorDir == false){
            m.addIntArg(0);
            m.addIntArg(1);
        }else{
            m.addIntArg(1);
            m.addIntArg(0);
        }
        
        m.addIntArg((int)vibeVal);
        
        mSender.sendMessage(m);
    }
    
    void vibeAuto(){
        if(isVibeAuto){
            
            if(ofGetElapsedTimef() - mElapsedTime > mVibeTimeSpan){
                mVibeCounter++;
                
                mElapsedTime = ofGetElapsedTimef();
                
                if(mVibeCounter == (int)mVibeTempo)mVibeCounter = 0;
                else vibe();
            }
            
        }
        
        if(ofGetElapsedTimef() - mElapsedTimeFromVibe > mVibeDur){
            mElapsedTimeFromVibe = ofGetElapsedTimef();
            mVibe.set(0);
        }
    }
    
    void draw(){
        
        float vibeVal = mSmoothedVibeVal.val;
        
        ramBeginCamera();
        
        if(isDrawFloor){
            ofPushMatrix();
            
            ofRotateX(90);
            ofScale(3.0,6.0);
            mDisplace.begin();
            mDisplace.setUniform1f("time", ofGetElapsedTimef());
            mDisplace.setUniform1f("val", vibeVal * 0.015);
            mPlane.drawWireframe();
            mDisplace.end();
            ofPopMatrix();
        }
        
        ramEndCamera();
        
    }
    
    
    
    void drawActor(const ramActor& actor){
        
        float vibeVal = mSmoothedVibeVal.val * 0.5;
        
        if(isDrawActor){
            
            for(int j = 0; j < actor.getNumNode(); j++){
                ramNode node = actor.getNode(j);
                
                float jointSize = (j == ramActor::JOINT_HEAD) ? 8.0 : 5.0;
                
                node.setGlobalPosition(node.getGlobalPosition() + ofPoint(ofSignedNoise(node.getGlobalPosition().x,
                                                                                        node.getGlobalPosition().y,
                                                                                        node.getGlobalPosition().z),
                                                                          ofSignedNoise(node.getGlobalPosition().z,
                                                                                        node.getGlobalPosition().x,
                                                                                        node.getGlobalPosition().y),
                                                                          ofSignedNoise(node.getGlobalPosition().z,
                                                                                        node.getGlobalPosition().y,
                                                                                        node.getGlobalPosition().x)) * vibeVal);
                
                ofDrawBox(node.getGlobalPosition(), jointSize + ofSignedNoise(node.getGlobalPosition().x,
                                                                              node.getGlobalPosition().y,
                                                                              node.getGlobalPosition().z) * vibeVal * 0.333);
                ramLine(node);
                
            }
        }
    }
    void onPanelChanged(ofxUIEventArgs& e)
	{
		string name = e.widget->getName();
        
        if(name == "vibe"){
            vibe();
        }
        
        ofxUIToggle *t = static_cast<ofxUIToggle *>(e.widget);
        
        string togName = e.widget->getName();
        
        if(togName == "JOINT_ABDOMEN")mJointNum = ramActor::JOINT_ABDOMEN;
        if(togName == "LEFT_WRIST")mJointNum = ramActor::JOINT_LEFT_WRIST;
        if(togName == "RIGHT_WRIST")mJointNum = ramActor::JOINT_RIGHT_WRIST;
        if(togName == "LEFT_ANKLE")mJointNum = ramActor::JOINT_LEFT_ANKLE;
        if(togName == "RIGHT_ANKLE")mJointNum = ramActor::JOINT_RIGHT_ANKLE;
	}
    
private:

    ofxOscSender mSender;
    float mVibeStrength = 200.0;
    float mVibeThresh = 100.0;
    static const int BEAM_NUM = 30;
    
    KezSlide mVibe;
    KezSlide mVibeFromActor;
    
    float mVibeTimeSpan = 0.2;
    float mElapsedTime = 0.0;
    float mVibeTempo = 4;
    float mVibeDur = 0.1;
    float mElapsedTimeFromVibe;
    
    int mVibeCounter = 0;
    int mJointNum = ramActor::JOINT_ABDOMEN;
    
    bool mMotorDir = 0;
    bool isDrawActor = true;
    bool isDrawFloor = false;
    bool isVibeAuto = false;
    bool isVibeWhenActorMoveFast = false;
    
    KezSlide mSmoothedVibeVal;

    float mLineWidth = 4.0;
    
    ofPlanePrimitive mPlane;
    string mFrag;
    string mVert;
    ofShader mDisplace;
    
};


#endif
