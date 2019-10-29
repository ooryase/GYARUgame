#pragma once
#include"VirtualScene.h"

class Attention : public VirtualScene
{
	const int texHandle;

	enum PhaseList
	{
		START,
		NEXT
	};
	PhaseList phase;

public:
	Attention();
	~Attention();

	void Update();
	void Draw() const;
};