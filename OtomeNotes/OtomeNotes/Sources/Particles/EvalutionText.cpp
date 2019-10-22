#include"EvalutionText.h"
#include"DxLib.h"
#include<iostream>

EvalutionText::EvalutionText(int x,int y,int _fontHandle,std::string _text,int _color) : VirtualParticle(x,y),
	fontHandle(_fontHandle),
	text(_text),
	color(_color)
{
	time = 0;
}

void EvalutionText::Update(int deltaTime)
{
	time += deltaTime;

	Dead = (time > 1000);
}

void EvalutionText::Draw() const
{
	DrawStringToHandle(baseX- 50, baseY - 100 - time / 10, text.c_str(), color, fontHandle);
}