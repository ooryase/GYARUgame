#include"Doyon.h"
#include"DxLib.h"
#include<iostream>

Doyon::Doyon(int x, int y, int _texHandle,int _size) : VirtualParticle(x, y),
texHandle(_texHandle),
size(_size)
{
	time = 0;
}

void Doyon::Update(int deltaTime)
{
	time += deltaTime;

	Dead = (time > 1000);
}

void Doyon::Draw() const
{
	if(time < 200)
		DrawExtendGraph(baseX- size, baseY - size + time / 10, baseX + size,baseY - size + size * time / 100 + time / 10,texHandle,TRUE);
	else if(time < 750)
		DrawExtendGraph(baseX - size, baseY - size + time / 10, baseX + size, baseY + size + time / 10, texHandle, TRUE);
	else if(time < 1020)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 1020 - time);
		DrawExtendGraph(baseX - size, baseY - size + time / 10, baseX + size, baseY + size + time / 10, texHandle, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}