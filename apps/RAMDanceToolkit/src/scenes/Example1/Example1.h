//
//  Example1.h
//  RAM Dance Toolkit
//
//  Created by James Kong on 22/10/2017.
//

#pragma once

#include "ramMain.h"


class Example1 : public rdtk::BaseScene
{
public:
    
    string getName() const { return "Example1"; }
    
    void setupControlPanel();
    void drawImGui();
    void setup();
    void update();
    void draw();
    void drawActor(const rdtk::Actor &actor);
    void drawRigid(rdtk::RigidBody &rigid);
    

};
