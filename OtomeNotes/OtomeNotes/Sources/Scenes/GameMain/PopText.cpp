#include"PopText.h"
#include"DxLib.h"
#include<iostream>

PopText::PopText(char* _text, int _x, int _y)
{
	std::memset(text, 0, sizeof(text));
	text[0] = _text[0];
	text[1] = _text[1];


	time = 0;
	x = baseX = _x;
	y = baseY = _y;
}

void PopText::Update(int deltaTime)
{
	time += deltaTime;

	if (time < 400)
		y = baseY - static_cast<int>((400 - time) * time / (255.0 * 255.0) * 30.0);
	else
		y = baseY;
}

void PopText::Draw(int fontHandle) const
{
	DrawStringToHandle(x, y, text, GetColor(255, 255, 255), fontHandle);
}

bool PopText::Dead()
{
	return false;
}