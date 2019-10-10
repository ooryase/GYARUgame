#pragma once
#include"VirtualScene.h"

class Title : public VirtualScene
{
public:
	Title();

	void Update();
	void Draw() const;
};
