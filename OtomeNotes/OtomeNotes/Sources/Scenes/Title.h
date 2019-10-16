#pragma once
#include"VirtualScene.h"

class Title : public VirtualScene
{
private:
	const int titleGraphHandle;
	const int textGraphHandle;
	const int movieHandle;

	enum TitlePhaseList
	{
		START,
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
