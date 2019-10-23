#include"NotesButton.h"
#include"DxLib.h"
#include<iostream>

NotesButton::NotesButton(int x, int y, int _texHandle) : VirtualParticle(x, y),
texHandle(_texHandle)
{
	time = 0;
}

void NotesButton::Update(int deltaTime)
{
	time += deltaTime;

	Dead = (time > 400);
}

void NotesButton::Draw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200 - time / 2);
	int temp = 70 + time / 35;
	DrawExtendGraph(baseX - temp, baseY - temp, baseX + temp, baseY + temp, texHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}