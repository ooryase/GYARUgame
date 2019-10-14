#pragma once
#include<vector>
#include"VirtualScene.h"

class StageSelect : public VirtualScene
{
private:
	std::vector<int> stageImageHandle;

	double radian;

public:
	StageSelect();
	~StageSelect();

	void Update();
	void Draw() const;
};