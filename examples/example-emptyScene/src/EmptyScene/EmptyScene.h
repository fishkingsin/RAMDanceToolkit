// 
// EmptyScene.h - RAMDanceToolkit
// 
// Copyright 2012-2013 YCAM InterLab, Yoshito Onishi, Satoru Higa, Motoi Shimizu, and Kyle McDonald
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

#pragma once

#include "ramMain.h"
using namespace rdtk;
class EmptyScene : public BaseScene
{

public:
	
	string getName() const { return "My scene"; }

    void setupControlPanel();
    void setup();
    void update();
    void draw();

    void drawActor(const Actor& actor);
    void drawRigid(const RigidBody &rigid);
    void onActorSetup(const Actor &actor);
    void onActorExit(const Actor &actor);
    void onRigidSetup(const RigidBody &rigid);
    void onRigidExit(const RigidBody &rigid);
	
private:
	
    void onPanelChanged(ofxUIEventArgs &e);
    
	float mySlider;
	bool myToggle;
};

