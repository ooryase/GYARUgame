#pragma once
#include<vector>
#include"VirtualScene.h"

class StageSelect : public VirtualScene
{
private:
	std::vector<std::pair<int,int>> stageImageHandle;
	int loadHandle;
	const int infoVoiceHandle;
	const int bgmHandle;
	const int pushSeHandle;
	const int backGraphHandle;
	const int fontHandle;

	double radian;
	const double PI;
	int selectStage;

	int pressTime;

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
	//int型のをdoubleで割った値をintに直して渡す
	int Perf(int i,double perf) const;

};