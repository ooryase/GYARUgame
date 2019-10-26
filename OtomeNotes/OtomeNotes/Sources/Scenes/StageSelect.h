#pragma once
#include<vector>
#include"VirtualScene.h"

class StageSelect : public VirtualScene
{
private:
	std::vector<int> stageImageHandle;
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
	//int型のをdoubleで割った値をintに直して渡す
	int Perf(int i,double perf) const;

};