#pragma once
#include<iostream>
#include"VirtualParticle.h"

class NotesButton : public VirtualParticle
{
private:
	const int texHandle;

	int time;

public:
	NotesButton(int x, int y, int _texHandle);

	void Update(int deltaTime);
	void Draw() const;
};