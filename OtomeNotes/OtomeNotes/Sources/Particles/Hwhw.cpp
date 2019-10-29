#include"Hwhw.h"
#include"DxLib.h"
#include<iostream>

Hwhw::Hwhw(int x, int y, int _texHandle, int _hue, double _rate) : VirtualParticle(x, y),
texHandle(_texHandle),
hue(_hue),
rate(_rate)
{
	time = 0;
}

void Hwhw::Update(int deltaTime)
{
	time += deltaTime;

	Dead = (time > 1000);
}

void Hwhw::Draw() const
{
	//GraphFilter(texHandle, DX_GRAPH_FILTER_HSB, 0, hue, 0, 0);

	auto alpha = static_cast<int>(time * (1000 - time) / 200.0);
	alpha = (alpha > 255) ? 255 : alpha;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	for (int i = 0; i < 10; i++)
	{
		DrawRotaGraph2(baseX + static_cast<int>((time + 200) * cos(i * 0.6) * 0.25), baseY + static_cast<int>((time + 200) * sin(i * 0.6) * 0.25),
			20, 20,
			rate, i / 2.5,//iTime / 120.0,
			texHandle, TRUE, i % 2);

	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}