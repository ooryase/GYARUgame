#pragma once
#include"VirtualScene.h"

class Title : public VirtualScene
{
private:
	const int titleGraphHandle;
	const int backGraphHandle;
	const int textGraphHandle;
	const int movieHandle;
	const int titleCallHandle;

	enum TitlePhaseList
	{
		START,
		DECISION,
		MOVIE,
		NEXT
	};

	TitlePhaseList phase;
	bool movieSkip;

public:
	Title();
	~Title();

	void Update();
	void Draw() const;

private:
	void DrawTitle() const;
	void DrawMovie() const;
};
