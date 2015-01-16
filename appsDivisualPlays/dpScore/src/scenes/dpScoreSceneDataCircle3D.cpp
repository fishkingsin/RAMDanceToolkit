//
//  dpScoreSceneDataCircle3D.cpp
//  dpScore
//
//  Created by YoshitoONISHI on 1/15/15.
//
//

#include "dpScoreSceneDataCircle3D.h"

DP_SCORE_NAMESPACE_BEGIN

SceneDataCircle3D::Circle::Circle()
{
    data.assign(kResolution, ofVec2f::zero());
}

void SceneDataCircle3D::Circle::update(const ofVec2f& v)
{
    data.push_back(ofVec2f(clamp(v.x), clamp(v.y)));
    while (data.size() > kResolution) {
        data.pop_front();
    }
}

void SceneDataCircle3D::Circle::draw()
{
    const float step = mRadius * TWO_PI / kResolution;
    for (int i=0; i<data.size(); i++) {
        const auto v = data.at(i);
        if (v.length() < 0.01f) continue;
        
        ofPushMatrix();
        const float angle = -360.f / kResolution * i;
        ofRotate(angle);
        ofTranslate(0.f, -mRadius);
        const float x = v.x * mRadius;
        ofFill();
        ofSetColor(128, 128);
        ofRect(-step*0.5f, 0.f, step, x);
        ofNoFill();
        ofSetLineWidth(2.f);
        ofSetColor(ofColor::white, 128);
        ofRect(-step*0.5f, 0.f, step, x);
        ofPopMatrix();
    }
    ofSetLineWidth(step);
    ofSetColor(color::kMain, 255);
    ofLine(0.f, -mRadius-50.f, 0.f, -mRadius+50.f);
    
}

#pragma mark ___________________________________________________________________
void SceneDataCircle3D::initialize()
{
    dpDebugFunc();
    
    mUICanvas = new ofxUICanvas();
    mUICanvas->setName(getName());
    mUICanvas->addLabel(getName());
    mUICanvas->addSpacer();
}

void SceneDataCircle3D::shutDown()
{
    dpDebugFunc();
    
    if (mUICanvas) {
        delete mUICanvas;
        mUICanvas = nullptr;
    }
}

void SceneDataCircle3D::enter()
{
    dpDebugFunc();
    
    mCircles.assign(kNumCircles, ofPtr<Circle>());
    for (auto& p : mCircles) {
        p = ofPtr<Circle>(new Circle());
    }
}

void SceneDataCircle3D::exit()
{
    dpDebugFunc();
}

void SceneDataCircle3D::update(ofxEventMessage& m)
{
    if (m.getAddress() == kOscAddrCaneraUnitVector) {
        
        for (int i=0; i<kNumCircles ; i++) {
            if (2*i+0 >= m.getNumArgs() || 2*i+1 >= m.getNumArgs()) break;
            
            ofVec2f v(m.getArgAsFloat(2*i+0), m.getArgAsFloat(2*i+1));
            mCircles.at(i)->update(v);
        }
    }
}

void SceneDataCircle3D::draw()
{
    ofPushMatrix();
    for (int i=0; i<mCircles.size(); i++) {
        ofPushMatrix();
        ofTranslate(kW*0.5f + getLineUped(kW, i/2, mCircles.size()/2), kH*0.5f);
        mCircles.at(i)->draw();
        ofPopMatrix();
    }
    ofPopMatrix();
}

DP_SCORE_NAMESPACE_END