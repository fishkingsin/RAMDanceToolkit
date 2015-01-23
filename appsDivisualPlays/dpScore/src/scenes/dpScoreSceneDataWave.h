//
//  dpScoreSceneDataWave.h
//  dpScore
//
//  Created by YoshitoONISHI on 1/15/15.
//
//

#ifndef __dpScore__dpScoreSceneDataWave__
#define __dpScore__dpScoreSceneDataWave__

#include "dpScoreSceneBase.h"

DP_SCORE_NAMESPACE_BEGIN

class SceneDataWave final : public SceneBase {
public:
    explicit SceneDataWave() = default;
    virtual ~SceneDataWave() = default;
    
    void initialize() override;
    void shutDown() override;
    
    void enter() override;
    void exit() override;
    
    void update(ofxEventMessage& m) override;
    void draw() override;
    
private:
    const int kNumX{kNumCameraunitVectors*2};
    const int kNumY{50};
    const float kStepX{80.f};
    const float kStepY{80.f};
    
    ofMesh mPlaneMesh;
    ofVbo mVbo;
    ofEasyCam mCam;
    
    ofTrueTypeFont mFont;
    
    vector<ofVec2f> mVectors;
    vector<deque<float> > mData;
    float mScale{200.f};
    float mEnterTime{0.f};
    

};

DP_SCORE_NAMESPACE_END

#endif /* defined(__dpScore__dpScoreSceneDataWave__) */
