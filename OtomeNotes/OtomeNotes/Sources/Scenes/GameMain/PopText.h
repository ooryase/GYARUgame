#pragma once

class PopText
{
private:
	int time;
	char text[256];
	int x, baseX, y, baseY;
	const int color;

public:
	PopText(char* _text, int _x, int _y,int _color);

	void Update(int deltaTime);
	void Draw(int fontHandle) const;

	bool Dead();
};