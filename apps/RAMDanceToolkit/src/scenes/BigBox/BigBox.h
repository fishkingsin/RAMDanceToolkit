// 
// BigBox.h - RAMDanceToolkit
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

class BigBox : public rdtk::BaseScene
{
	vector<float> mSizeArray;
	float mBoxLineWidth;
	float mMasterBoxSize;
    float mSphereRes;
	bool mUseSingleColor;
    int mPolygonType;
	ofFloatColor mLineColor;
    vector<string> polygontype;
    ofxUIRadio *radioButton;
    
	
public:

	BigBox() : mBoxLineWidth(2.0), mMasterBoxSize(300.0), mUseSingleColor(true), mLineColor(0.840, 1.000, 0.419),mSphereRes(16),mPolygonType(0)
	{
		mSizeArray.clear();
		mSizeArray.resize(rdtk::Actor::NUM_JOINTS);
		for (int i=0; i<mSizeArray.size(); i++)
			mSizeArray.at(i) = mMasterBoxSize;
	}

	void setupControlPanel()
	{
#ifdef RAM_GUI_SYSTEM_OFXUI
		
		rdtk::GetGUI().addToggle("Use single color", &mUseSingleColor);
        
        polygontype.push_back("Box");
        polygontype.push_back("Sphere");
        polygontype.push_back("Plain");
        mPolygonType = 0;
        radioButton = rdtk::GetGUI().addRadioGroup("Polygon", polygontype, &mPolygonType);
		rdtk::GetGUI().addColorSelector("line color", &mLineColor);
		rdtk::GetGUI().addSlider("Line width", 0.0, 10.0, &mBoxLineWidth);
        rdtk::GetGUI().addSlider("Sphere Resolution", 0.0, 32.0, &mSphereRes);
		rdtk::GetGUI().addSlider("Master box size", 0.0, 1000.0, &mMasterBoxSize);

		for (int i=0; i<rdtk::Actor::NUM_JOINTS; i++)
			rdtk::GetGUI().addSlider(rdtk::Actor::getJointName(i), 0.0, 1000.0, &mSizeArray.at(i));

		ofAddListener(rdtk::GetGUI().getCurrentUIContext()->newGUIEvent, this, &BigBox::onPanelChanged);
		
#endif
	}
	
	void onPanelChanged(ofxUIEventArgs& e)
	{
		string name = e.widget->getName();
		
		if (name == "Master box size")
		{
			for (int i=0; i<mSizeArray.size(); i++)
				mSizeArray.at(i) = mMasterBoxSize;
        }else if (name == "Sphere Resolution"){
            ofSetSphereResolution(mSphereRes);
        }
        
	}
	
	void drawImGui()
	{
		ImGui::Checkbox("Use single color", &mUseSingleColor);
		ImGui::ColorEdit3("Line color", &mLineColor[0]);
		ImGui::DragFloat("Line width", &mBoxLineWidth, 0.1, 0.0, 10.0);
		if (ImGui::DragFloat("Master box size", &mMasterBoxSize, 1, 0, 1000.0))
		{
			for (int i=0; i<mSizeArray.size(); i++)
				mSizeArray.at(i) = mMasterBoxSize;
		}
		
		ImGui::Columns(2, NULL, true);
		for (int i=0; i<rdtk::Actor::NUM_JOINTS; i++)
		{
			ImGui::DragFloat(rdtk::Actor::getJointName(i).c_str(), &mSizeArray.at(i), 1, 0, 1000);
			ImGui::NextColumn();
		}
		ImGui::Columns(1);
		
	}
	
	void draw()
	{
		rdtk::BeginCamera();
		
		for(int i=0; i<getNumNodeArray(); i++)
		{
			const rdtk::NodeArray &NA = getNodeArray(i);
			drawBigBox(NA);
		}
		
		rdtk::EndCamera();
	}
	
	void drawBigBox(const rdtk::NodeArray& NA)
	{
		for (int i=0; i<NA.getNumNode(); i++)
		{
			const int keyJoint = NA.isActor() ? rdtk::Actor::JOINT_HEAD : 0;
			
			const rdtk::Node &node = NA.getNode(i);
			float boxSize = (i==keyJoint) ? 6 : 3;
			float bigBoxSize = mSizeArray.at(i);
			
			glPushAttrib(GL_ALL_ATTRIB_BITS);
			glPushMatrix();
			{
				ofPushStyle();
				ofNoFill();
				
				glEnable(GL_DEPTH_TEST);
				
				/*!
				 big box
				 */
				if (mUseSingleColor)
				{
					ofSetColor(mLineColor);
				}
				else
				{
					if (i%3 == 0)
					{
						ofSetColor( rdtk::Color::BLUE_DEEP );
					}
					else if (i%3 == 1)
					{
						ofSetColor( rdtk::Color::BLUE_NORMAL );
					}
					else
					{
						ofSetColor( rdtk::Color::BLUE_LIGHT );
					}
				}
				
				ofSetLineWidth(mBoxLineWidth);
				node.beginTransform();
				
                switch(mPolygonType){
                    case 0:
                        ofDrawBox(bigBoxSize);
                        break;
                    case 1:
                        ofDrawSphere(0, 0, bigBoxSize);
                        break;
                    case 2:
                        ofDrawPlane(0, 0, bigBoxSize, bigBoxSize);
                        break;
                    default:
                        ofDrawBox(bigBoxSize);
                        break;
                    
                }
				node.endTransform();
				
				ofPopStyle();
			}
			glPopMatrix();
			glPopAttrib();
		}
	}
	
	string getName() const { return "Big Box"; }
};
