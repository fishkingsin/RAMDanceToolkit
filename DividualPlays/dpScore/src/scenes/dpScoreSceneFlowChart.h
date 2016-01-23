//
//  dpScoreSceneFlowChart.h
//  dpScore
//
//  Created by YoshitoONISHI on 1/19/16.
//
//

#ifndef dpScoreSceneFlowChart_h
#define dpScoreSceneFlowChart_h

#include "dpScoreSceneBodyBase.h"
#include "dpScoreBaseNode.h"
#include "ofxMotioner.h"

DP_SCORE_NAMESPACE_BEGIN

class NodeSkeleton : public ofxMot::Node {
public:
    void customDraw() override;
};

class SceneFlowChart final: public SceneBodyBase<NodeSkeleton> {
public:
	enum NodeType {
		NODE_MOTIONER = 0,
		NODE_MASTER_HAKONIWA,
		NODE_STAGE,
		NODE_HAKONIWA,
		NODE_CAMERA_UNIT,
		NODE_DISPLAY,
		NODE_SPEAKER,
		NODE_LIGHT,
		NODE_COMPUTER,
		NODE_AUDIENCE,
		NUM_NODES,
	};
    
    enum CamMode {
        CAM_MOVE,
        CAM_MAIN,
        CAM_EASY,
        N_CAM_MODE,
    };

	explicit SceneFlowChart() = default;
	virtual ~SceneFlowChart() = default;
	SceneFlowChart(const SceneFlowChart &) = delete;
	SceneFlowChart& operator = (const SceneFlowChart&) = delete;

	void initialize() override;
	void shutDown() override;

	void enter() override;
	void exit() override;

	void update(ofxEventMessage& m) override;
	void draw() override;

	void keyPressed(int key) override;

private:
    void drawScene();
    
    void changeCamMode(CamMode m);
    int getCurrentCamID() const;
    int getNextCamID() const;
    
    template <class T> ofPtr<T> getNode(int idx) { return dynamic_pointer_cast<T>(mNodes.at(idx)); }
    
	ofTrueTypeFont mFont;
	vector<ofPtr<BaseNode> > mNodes;
	vector<ofCamera> mCams;
    vector<int> mCamOrders;
	ofCamera mCurrentCam;
    ofCamera mCamMain;
    ofNode mCamMainParent;
	ofEasyCam mCamEasy;
    CamMode mCamMode;
	int mCurrentCamOrderIdx {0};
	
    struct PP { ofVec3f p0, p1; };
    vector<PP> mPoints;
    int mCurrentLine {0};
    
    float mElapsedTimeMove {0.f};
    float mElapsedTimeMainCam {0.f};
    float mElapsedTimeLine {0.f};
};

DP_SCORE_NAMESPACE_END

#endif /* dpScoreSceneFlowChart_h */
