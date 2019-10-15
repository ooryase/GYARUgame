#pragma once
#include<vector>
#include"VirtualScene.h"

class StageSelect : public VirtualScene
{
private:
	std::vector<int> stageImageHandle;

	double radian;
	const double PI;
	int selectStage;

	enum RoratePhase
	{
		START,
		ROTATE,
		STOP,
		DECISION
	};
	RoratePhase rotatePhase;
public:
	StageSelect();
	~StageSelect();

	void Update();
	void Draw() const;
};