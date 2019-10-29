#pragma once
#include<iostream>
#include"VirtualParticle.h"

class Doyon : public VirtualParticle
{
private:
	const int texHandle;
	//const int hue;
	const int size;

	int time;

public:
	Doyon(int x, int y, int _texHandle,int _size);

	void Update(int deltaTime);
	void Draw() const;
};