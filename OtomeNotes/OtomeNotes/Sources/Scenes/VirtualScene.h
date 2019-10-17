#pragma once
#include<iostream>
#include"../MainController/TimeManager.h"

class VirtualScene
{
protected:
	std::shared_ptr<VirtualScene> nextScene;

	std::shared_ptr<TimeManager> time;

public:
	VirtualScene();

	void virtual Update() = 0;

	void virtual Draw() const = 0;

	std::shared_ptr<VirtualScene> GetNextScene();
};