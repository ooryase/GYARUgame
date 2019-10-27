#include"Krkr.h"
#include"DxLib.h"
#include<iostream>

Krkr::Krkr(int x, int y, int _texHandle, int _hue,double _rate) : VirtualParticle(x, y),
texHandle(_texHandle),
hue(_hue),
rate(_rate)
{
	time = 0;
}

void Krkr::Update(int deltaTime)
{
	time += deltaTime;

	Dead = (time > 400);
}

void Krkr::Draw() const
{
	GraphFilter(texHandle, DX_GRAPH_FILTER_HSB, 0, hue, 0, 0);

	for (int i = 0; i < 10; i++)
	{
		//auto iTime = time - i * 50;
		//if (iTime < 0 || 500 < iTime)
		//	continue;

		auto alpha = time * (400 - time) / 150;
		alpha = (alpha > 255) ? 255 : alpha;

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawRotaGraph2(baseX + static_cast<int>(cos(i * 0.6) * 0.25 * time), baseY + static_cast<int>(sin(i * 0.6) * 0.25 * time),
			20, 20,
			rate, i / 2.5,//iTime / 120.0,
			texHandle, TRUE, i % 2);

	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}