#pragma once
#include<iostream>
#include"VirtualParticle.h"

class Krkr : public VirtualParticle
{
private:
	const int texHandle;
	const int hue;

	int time;

public:
	Krkr(int x, int y, int _texHandle, int _hue);

	void Update(int deltaTime);
	void Draw() const;
};