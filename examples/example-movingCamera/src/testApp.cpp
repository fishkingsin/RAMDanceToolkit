// 
// testApp.cpp - RAMDanceToolkit
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

#include "testApp.h"


#pragma mark - oF methods
//--------------------------------------------------------------
void testApp::setup()
{
	ofSetFrameRate(60);
	ofSetVerticalSync(true);


	///  setup
	// ------------------
	Initialize(10000);

	SceneManager &sceneManager = SceneManager::instance();
    mover = ofPtr<CameraMover>(new CameraMover);
	sceneManager.addScene(mover);
}

//--------------------------------------------------------------
void testApp::update()
{
	
}

//--------------------------------------------------------------
void testApp::draw()
{
	
}



#pragma mark -  methods
//--------------------------------------------------------------
void testApp::drawActor(const Actor &actor)
{
	ofSetColor(Color::GREEN_LIGHT);
	DrawBasicActor(actor);
}

//--------------------------------------------------------------
void testApp::drawRigid(const RigidBody &rigid)
{

}


#pragma mark -  Events
//--------------------------------------------------------------
void testApp::onActorSetup(const Actor &actor)
{
	
}

//--------------------------------------------------------------
void testApp::onActorExit(const Actor &actor)
{
	
}

//--------------------------------------------------------------
void testApp::onRigidSetup(const RigidBody &rigid)
{
	
}

//--------------------------------------------------------------
void testApp::onRigidExit(const RigidBody &rigid)
{
	
}


#pragma mark - of Events
//--------------------------------------------------------------
void testApp::keyPressed(int key)
{

}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{

}
