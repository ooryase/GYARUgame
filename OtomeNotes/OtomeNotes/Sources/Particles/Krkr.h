#pragma once
#include<iostream>
#include"VirtualParticle.h"

class Krkr : public VirtualParticle
{
private:
	const int texHandle;
	const int hue;
	const int rate;

	int time;

public:
	Krkr(int x, int y, int _texHandle, int _hue,double _rate);

	void Update(int deltaTime);
	void Draw() const;
};