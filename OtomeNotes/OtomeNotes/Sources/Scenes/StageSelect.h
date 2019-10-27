#pragma once
#include<vector>
#include"VirtualScene.h"

class StageSelect : public VirtualScene
{
private:
	std::vector<std::pair<int,int>> stageImageHandle;
	int loadHandle;

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
	void RotateUpdate();
	void Draw() const;
private:
	//intŒ^‚Ì‚ðdouble‚ÅŠ„‚Á‚½’l‚ðint‚É’¼‚µ‚Ä“n‚·
	int Perf(int i,double perf) const;

};