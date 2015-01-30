//
//  dpCameraUnit_Controller.cpp
//  dpHakoniwa_cameraUnit
//
//  Created by Ovis aries on 2014/12/19.
//
//

#include "dpCameraUnit_Controller.h"

dpCameraUnit_Controller::dpCameraUnit_Controller(){

	for (int i = 0;i < 4;i++){
		cvAnalysis[i].mGui.setPosition(-1000, 0);
		cvAnalysis[i].oscListPtr = &oscSendList;
		cvAnalysis[i].pairFXUnit = &cvFXUnit[i];
		cvFXUnit[i].mGui.setPosition(-1000, 0);
	}

	cvAnalysis[0].hakoniwa_name = "";
	cvAnalysis[1].hakoniwa_name = "";
	cvAnalysis[2].hakoniwa_name = "";
	cvAnalysis[3].hakoniwa_name = "";

	gui.setup();
	gui.addLabel("main Console");
	gui.addSpacer();
	gui.setTriggerWidgetsUponLoad(false);
	gui.addLabel("OSC SplitList",OFX_UI_FONT_LARGE);
	gui.addLabel("RDTK_1");
	gui.addTextInput("OSC_A", "192.168.20.2")->setAutoClear(false);
	gui.addLabel("RDTK_2");
	gui.addTextInput("OSC_B", "192.168.20.3")->setAutoClear(false);

	gui.addLabel("Score");
	gui.addTextInput("OSC_C", "192.168.20.11")->setAutoClear(false);
	gui.addLabel("Floor");
	gui.addTextInput("OSC_D", "192.168.20.6")->setAutoClear(false);
	gui.addLabel("Lighting");
	gui.addTextInput("OSC_E", "192.168.20.8")->setAutoClear(false);

	gui.addLabel("Audio2_evala");
	gui.addTextInput("OSC_F", "192.168.20.10")->setAutoClear(false);

	gui.addLabel("Dev_Sheep");
	gui.addTextInput("OSC_G", "192.168.20.36")->setAutoClear(false);
	gui.addLabel("Dev_Kez");
	gui.addTextInput("OSC_H", "192.168.20.23")->setAutoClear(false);
    gui.addLabel("Dev_Onishi");
    gui.addTextInput("OSC_I", "192.168.20.7")->setAutoClear(false);
    gui.addLabel("Dev_Onishi");
    gui.addTextInput("OSC_J", "192.168.20.30")->setAutoClear(false);
	gui.addSpacer();
	gui.addLabel("Preset Settings");
	gui.addToggle("SettingMode", &mbMakeSettings);
	gui.addIntSlider("Channel", 0, 3, &makeSettings_targetInput);

	refleshAddressList();

	gui.autoSizeToFitWidgets();
	makeSettings_targetInput = 1;
	ofAddListener(gui.newGUIEvent, this, &dpCameraUnit_Controller::guiEvent);

}

dpCameraUnit_Controller::~dpCameraUnit_Controller(){

}

void dpCameraUnit_Controller::update(){
	static bool init = true;
	if (init){
		init = false;
		cvFXUnit  [3].loadPreset("ColorOfWater");
		cvAnalysis[3].loadPreset("ColorOfWater");
	}

	static bool windowReShape;
	if (mbMakeSettings){
		if (mbMakeSettings != windowReShape) ofSetWindowShape(635, 1080);
	}else{
		if (mbMakeSettings != windowReShape) ofSetWindowShape(1920, 1080);
	}
	windowReShape = mbMakeSettings;

	inputUnit	.update();
	
	if (inputUnit.mFourSplit){
		if (mbMakeSettings){
			cvFXUnit[0].update(inputUnit.mFinalSource_FourSplit[makeSettings_targetInput],
							   inputUnit.mIsFrameNew);
			cvAnalysis[0].update(cvFXUnit[0].mSource,
								 cvFXUnit[0].mGraySource,
								 inputUnit.mIsFrameNew);
		}else{
			for (int i = 0;i < 4;i++){
				cvFXUnit[i]  .update(inputUnit.mFinalSource_FourSplit[i],
									 inputUnit.mIsFrameNew);
				cvAnalysis[i].update(cvFXUnit[i].mSource,
									 cvFXUnit[i].mGraySource,
									 inputUnit.mIsFrameNew);
			}
		}

	}else{
		cvFXUnit[0]		.update(inputUnit.mFinalSource_Small, inputUnit.mIsFrameNew);
		cvAnalysis[0]	.update(cvFXUnit[0].mSource, cvFXUnit[0].mGraySource, inputUnit.mIsFrameNew);
	}
	
	if (ofGetKeyPressed(' ')){
		for (int i = 0; i < 4;i++){
			cvFXUnit[i]		.savePreset(cvAnalysis[i].hakoniwa_name);
			cvAnalysis[i]	.savePreset(cvAnalysis[i].hakoniwa_name);
		}
	}

	if (ofGetFrameNum() % 300 == 0){
		for (int i = 0; i < 4;i++){
			cvFXUnit[i]		.savePreset(cvAnalysis[i].hakoniwa_name);
			cvAnalysis[i]	.savePreset(cvAnalysis[i].hakoniwa_name);
		}
	}
}

void dpCameraUnit_Controller::draw(){

	inputUnit.drawUI(0, 730);
	inputUnit.drawThumbnail(0, 840, 0.5);

	if (inputUnit.mFourSplit){
		for (int i = 0;i < 4;i++){

			ofSetColor(50 + 40 * (i % 2));
			ofRect(210 + i * 420, 0, 420, ofGetHeight());

			ofSetColor(255);
			cvFXUnit[i].drawUI			(210 + i*420, 0);
			cvFXUnit[i].drawThumbnail	(210 + i*420, ofGetHeight() - 300, 0.5);

			cvAnalysis[i].drawUI		(420 + i * 420, 0);
			cvAnalysis[i].drawThumbnail	(420 + i * 420, ofGetHeight() - 300, 0.5);


		}
	}else{

		cvFXUnit[0].draw(210,0);
		cvAnalysis[0].draw(420,0);

	}
}

void dpCameraUnit_Controller::simulator_initialize(){
	for (int i = 0;i < inputUnit.mCameraList.size();i++){
		if (inputUnit.mCameraList[i] == "Video") inputUnit.mSourceType = i;
	}
	inputUnit.mVideoPlayer.play();
	inputUnit.mFourSplit = true;

//	cvFXUnit_second		.mEnableFrameDiff = true;
//
//
//	cvAnalysis			.mEnableOptFlow = true;
//	cvAnalysis_second	.mEnableOptFlow = true;
//
//	cvAnalysis			.mEnableSendOSC = true;
//	cvAnalysis_second	.mEnableSendOSC = true;
}

void dpCameraUnit_Controller::guiEvent(ofxUIEventArgs &e){
	
	ofxUIWidget* w = e.widget;

	if (w->getName().substr(0,4) == "OSC_"){
		refleshAddressList();
	}
	
	if (w->getName() == "Load Setting"){

	}
	
	if (w->getName() == "Save Setting"){
		inputUnit.mGui.saveSettings("inputUnit.xml");
		
		for (int i = 0;i < 4;i++){
			cvFXUnit[i]		.mGui.saveSettings("cvFxUnit_"+ofToString(i)+".xml");
			cvAnalysis[i]	.mGui.saveSettings("Analysis_"+ofToString(i)+".xml");
		}
	}

	if (w->getName().substr(0,10) == "LoadPreset"){
		ofxUIToggle* tm = (ofxUIToggle*)(e.widget);

		int i = ofToInt(w->getName().substr(11,1));
		int j = ofToInt(w->getName().substr(14,1));

		gui.loadSettings("Preset"+ofToString(i)+ofToString(j)+"/Controller.xml");
		inputUnit.mGui.loadSettings("Preset"+ofToString(i)+ofToString(j)+"/inputUnit.xml");
		inputUnit.sourceReflesh();

		for (int o = 0;o < 4;o++){
			cvFXUnit[o].mGui.loadSettings("Preset"+ofToString(i)+ofToString(j)+"/cvFxUnit_"+ofToString(o)+".xml");
			cvAnalysis[o].mGui.loadSettings("Preset"+ofToString(i)+ofToString(j)+"/Analysis_"+ofToString(o)+".xml");
		}
		
	}
	
	if (w->getName().substr(0,10) == "SavePreset"){
		ofxUIToggle* tm = (ofxUIToggle*)(e.widget);

		int i = ofToInt(w->getName().substr(11,1));
		int j = ofToInt(w->getName().substr(14,1));

		ofDirectory::createDirectory("Preset"+ofToString(i)+ofToString(j));
		
		gui.saveSettings("Preset"+ofToString(i)+ofToString(j)+"/Controller.xml");
		inputUnit.mGui.saveSettings("Preset"+ofToString(i)+ofToString(j)+"/inputUnit.xml");
		
		for (int o = 0;o < 4;o++){
			cvFXUnit[o].mGui.saveSettings("Preset"+ofToString(i)+ofToString(j)+"/cvFxUnit_"+ofToString(o)+".xml");
			cvAnalysis[o].mGui.saveSettings("Preset"+ofToString(i)+ofToString(j)+"/Analysis_"+ofToString(o)+".xml");
		}
		
	}
	
	if (w->getName() == "namePreset"){
		ofxUITextInput* ti = (ofxUITextInput*)(e.widget);
		ti->setTextString(ti->getTextString());
	}

	if (w->getName() == "SaveHakoPreset"){
		for (int i = 0; i < 4;i++){
			cvFXUnit[i]		.savePreset(cvAnalysis[i].hakoniwa_name);
			cvAnalysis[i]	.savePreset(cvAnalysis[i].hakoniwa_name);
		}
	}
}

void dpCameraUnit_Controller::refleshAddressList(){
	oscSendList.clear();

	for (int i = 0;i < 10;i++){
		string wname = "OSC_"+ofToString(char(0x41+i));
		string add = ((ofxUITextInput*)
					  (gui.getWidget(wname)))->getTextString();

		oscSendList.push_back(add);
	}
}