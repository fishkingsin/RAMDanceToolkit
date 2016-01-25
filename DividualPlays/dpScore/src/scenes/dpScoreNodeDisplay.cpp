//
//  dpScoreNodeDisplay.cpp
//  dpScore
//
//  Created by YoshitoONISHI on 1/20/16.
//
//

#include "dpScoreNodeDisplay.h"
#include "dpScoreScoped.h"
#include "dpScoreToolBox.h"
#include "dpScoreObjects.h"
#include "dpScoreNodeStage.h"

DP_SCORE_NAMESPACE_BEGIN

NodeDisplay::NodeDisplay()
{
    title = "Displays";
    titleJP = "ディスプレイ";
    descriptionJP = "ディスプレイにツールキットで生成したダンサーへの情報を表示";
    
	addAimingOffset(getFrontLeft() + ofVec3f(getFrontDisplayWidth() * 0.5f - 8.f,
	                                         getFrontDisplayHeight() * 0.5f,
	                                         getFrontDisplayDepth() * 0.5f + 25.f));

	addAimingOffset(getFrontRight() + ofVec3f(getFrontDisplayWidth() * 0.5f - 4.f,
	                                          getFrontDisplayHeight() * 0.5f,
	                                          getFrontDisplayDepth() * 0.5f - 28.f));

	addAimingOffset(getRearLeft() + ofVec3f(getRearDisplayWidth() * 0.5f,
	                                        getRearDisplayHeight() * 0.5f,
	                                        getRearDisplayDepth() * 0.5f));

	addAimingOffset(getRearRight() + ofVec3f(getRearDisplayWidth() * 0.5f,
                                             getRearDisplayHeight() * 0.5f,
                                             getRearDisplayDepth() * 0.5f));
	getCamera().setFov(35.f);
	getCamera().setPosition(-NodeStage::kWidth * 0.5f + 80.f, 55.f, 200.f);
	getCamera().setOrientation(ofVec3f(0.f, 150.f, 0.f));

	const int fboSize {4};
	fbo.allocate(getFrontDisplayWidth() * fboSize, getFrontDisplayHeight() * fboSize);
}

NodeDisplay::~NodeDisplay()
{

}

void NodeDisplay::customDraw()
{
	ScopedStyle s;
	setStyle(*this);
	{
		const float w {getRearDisplayWidth()};
		const float h {getRearDisplayHeight()};
		const float d {getRearDisplayDepth()};
		{
			ScopedMatrix m;
			ofTranslate(getRearLeft());
			ofRotateX(getRearDisplayAngle());
			drawBox(ofVec3f::zero(), w, h, d);
		}
		{
			ScopedMatrix m;
			ofTranslate(getRearRight());
			ofRotateX(getRearDisplayAngle());
			drawBox(ofVec3f::zero(), w, h, d);
		}
	}
	{
		const float w {getFrontDisplayWidth()};
		const float h {getFrontDisplayHeight()};
		const float d {getFrontDisplayDepth()};
		const float wireOffset {20.f};

		auto drawFbo = [&]() {
				       ScopedStyle s;
				       ofFill();
				       ofSetColor(ofColor::white);
				       fbo.draw(0.f, 0.f, getFrontDisplayWidth(), getFrontDisplayHeight());
				       ScopedTranslate t(0.f, 0.f, getFrontDisplayDepth());
				       ofSetColor(ofColor::black);
				       ofRect(0.f, 0.f, getFrontDisplayWidth(), getFrontDisplayHeight());
			       };

		{
			ScopedMatrix m;
			ofTranslate(getFrontLeft());
			ofRotateY(-getFrontDisplayAngle());
			ofLine(ofVec3f(w * 0.5f - wireOffset, h, d * 0.5f), ofVec3f(w * 0.5f - wireOffset, h, d * 0.5f));
			ofLine(ofVec3f(w * 0.5f + wireOffset, h, d * 0.5f), ofVec3f(w * 0.5f + wireOffset, h, d * 0.5f));
			drawBox(ofVec3f::zero(), w, h, d);

			drawFbo();
		}
		{
			ScopedMatrix m;
			ofTranslate(getFrontRight());
			ofRotateY(getFrontDisplayAngle());
			ofLine(ofVec3f(w * 0.5f - wireOffset, h, d * 0.5f), ofVec3f(w * 0.5f - wireOffset, h, d * 0.5f));
			ofLine(ofVec3f(w * 0.5f + wireOffset, h, d * 0.5f), ofVec3f(w * 0.5f + wireOffset, h, d * 0.5f));
			drawBox(ofVec3f::zero(), w, h, d);

			drawFbo();
		}
	}
}

ofVec3f NodeDisplay::getFrontLeft()
{
    return ofVec3f(-NodeStage::kWidth * 0.5f - 61.f, 214.f, NodeStage::kDepth * 0.5f - 50.f);
}
ofVec3f NodeDisplay::getFrontRight()
{
    return ofVec3f(NodeStage::kWidth * 0.5f + 61.f, 214.f, NodeStage::kDepth * 0.5f - 50.f);
}
float NodeDisplay::getFrontDisplayWidth()
{
    return 104.f;
}
float NodeDisplay::getFrontDisplayHeight()
{
    return 61.4f;
}
float NodeDisplay::getFrontDisplayDepth()
{
    return 3.f;
}
float NodeDisplay::getFrontDisplayAngle()
{
    return 30.f;
}

ofVec3f NodeDisplay::getRearLeft()
{
    return ofVec3f(-NodeStage::kWidth * 0.5f, 0.f, -NodeStage::kDepth * 0.5f - 10.f);
}
ofVec3f NodeDisplay::getRearRight()
{
    return ofVec3f(NodeStage::kWidth * 0.5f - getRearDisplayWidth(), 0.f, -NodeStage::kDepth * 0.5f - 10.f);
}
float NodeDisplay::getRearDisplayWidth()
{
   return 104.f;
}
float NodeDisplay::getRearDisplayHeight()
{
    return 61.4f;
}
float NodeDisplay::getRearDisplayDepth()
{
    return 3.f;
}
float NodeDisplay::getRearDisplayAngle()
{
    return -30.f;
}

DP_SCORE_NAMESPACE_END