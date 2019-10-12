#include<iostream>
#pragma once

class VirtualScene
{
protected:
	std::shared_ptr<VirtualScene> nextScene;

public:
	VirtualScene();

	void virtual Update() = 0;

	void virtual Draw() const = 0;

	std::shared_ptr<VirtualScene> GetNextScene();
};