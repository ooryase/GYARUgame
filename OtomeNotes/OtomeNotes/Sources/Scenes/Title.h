#pragma once
#include"VirtualScene.h"

class Title : public VirtualScene
{
private:
	const int titleGraphHandle;
	const int backGraphHandle;
	const int backGraph2Handle;
	const int textGraphHandle;
	const int movieHandle;
	const int bgmHandle;
	const int titleCallHandle;
	const int pushSeHandle;

	enum TitlePhaseList
	{
		START,
		DECISION,
		MOVIE,
		NEXT
	};

	TitlePhaseList phase;
	bool movieSkip;

	int time2;

public:
	Title();
	~Title();

	void Update();
	void Draw() const;

private:
	void DrawTitle() const;
	void DrawMovie() const;
	void DrawDecision() const;
};
