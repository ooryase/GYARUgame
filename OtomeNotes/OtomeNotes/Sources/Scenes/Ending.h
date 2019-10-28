#pragma once
#include"VirtualScene.h"

class Ending : public VirtualScene
{
private:
	const int backGraphHandle;
	const int textGraphHandle;
	const int endCallHandle;

	enum PhaseList
	{
		START,
		NEXT
	};

	PhaseList phase;

public:
	Ending();
	~Ending();

	void Update();
	void Draw() const;
};
