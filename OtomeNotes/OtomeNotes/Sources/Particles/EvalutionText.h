#pragma once
#include<iostream>
#include"VirtualParticle.h"

class EvalutionText : public VirtualParticle
{
private:
	const int fontHandle;
	const std::string text;
	const int color;

	int time;

public:
	EvalutionText(int x,int y,int _fontHandle,std::string _text, int _color);

	void Update(int deltaTime);
	void Draw() const;
};