//
//  BodyBreak.hpp
//  RAM Dance Toolkit
//
//  Created by James Kong on 25/10/2017.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// YCAM "RAM CAMP in Kyoto 2017, Kyoto Experiment 2017
#pragma once
#include "ramMain.h"

class BodyBreak : public rdtk::BaseScene
{
    vector<float> mSizeArray;
    float mMasterBoxSize;
    float mSphereRes;
    float mThreshold;
public:
    BodyBreak() : mSphereRes(8), mMasterBoxSize(32), mThreshold(0.5){
//        mSizeArray.clear();
//        mSizeArray.resize(rdtk::Actor::NUM_JOINTS);
//        for (int i=0; i<mSizeArray.size(); i++)
//            mSizeArray.at(i) = ofRandom(mMasterBoxSize*0.5,mMasterBoxSize);
//        ofPoint iniPos(0,0,0); //the position is refering to the center of the grid
//        ofPoint gridSize(1000, 1000, 1000);
//        int gridResX = 30;
//        int gridResY = 30;
//        int gridResZ = 30;
//        marchingCubes.init(iniPos, gridSize, gridResX, gridResY, gridResZ);
    }
    void setupControlPanel()
    {
//#ifdef RAM_GUI_SYSTEM_OFXUI
//
//        rdtk::GetGUI().addSlider("Sphere Resolution", 0.0, 32.0, &mSphereRes);
//        rdtk::GetGUI().addSlider("Master box size", 0.0, 1000.0, &mMasterBoxSize);
//        rdtk::GetGUI().addSlider("Threshold", 0.0, 1.0, &mThreshold);
//        for (int i=0; i<rdtk::Actor::NUM_JOINTS; i++)
//            rdtk::GetGUI().addSlider(rdtk::Actor::getJointName(i), 0.0, 1000.0, &mSizeArray.at(i));
//
//        ofAddListener(rdtk::GetGUI().getCurrentUIContext()->newGUIEvent, this, &PolygonMan::onPanelChanged);
//#endif
    }
    void onPanelChanged(ofxUIEventArgs& e)
    {
//        string name = e.widget->getName();
//        if (name == "Master box size")
//        {
//            for (int i=0; i<mSizeArray.size(); i++)
//                mSizeArray.at(i) = mMasterBoxSize;
//        }else if (name == "Sphere Resolution"){
//            ofSetSphereResolution(mSphereRes);
//        }
    }
    void drawImGui()
    {
    }
    void update(){
//        for(int i=0; i<getNumNodeArray(); i++)
//        {
//            const rdtk::NodeArray &NA = getNodeArray(i);
//            drawBigBox(NA);
//        }
    }
    void draw()
    {
        rdtk::BeginCamera();
        
        ofSetColor(0.0f, 0.0f, 0.0f);
//        marchingCubes.debugDraw();
        
        rdtk::EndCamera();
    }
#pragma mark -
    //--------------------------------------------------------------
    void drawActor(const rdtk::Actor &actor)
    {
        ofSetColor(rdtk::Color::RED_DEEP);
        rdtk::DrawBasicActor(actor);
        
    }

    string getName() const { return "Polygon Man"; }
};

