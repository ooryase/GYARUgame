#pragma once
#include<iostream>
#include"VirtualParticle.h"

class Hwhw : public VirtualParticle
{
private:
	const int texHandle;
	const int hue;
	const double rate;

	int time;

public:
	Hwhw(int x, int y, int _texHandle, int _hue, double _rate);

	void Update(int deltaTime);
	void Draw() const;
};