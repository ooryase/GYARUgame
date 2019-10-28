#include"DxLib.h"
#include"Button.h"

Button::Button(int _texHandle[], int _popToJustTime) :
	baseX(200),
	baseY(550),
	notesPopToJustTime(_popToJustTime)
{
	memcpy(texHandle, _texHandle, sizeof(texHandle));
	time = 0;
	end = false;
	endTimer = 0;
	Dead = false;
}

void Button::Update(int deltaTime)
{
	time += deltaTime;

	if (end)
	{
		endTimer += deltaTime;
		
		Dead = (endTimer > 1800);
	}
}

void Button::Draw() const
{
	if (end && endTimer > 1800 - 510)
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, (1800 - endTimer) / 2);
		DrawGraph(time / 5 - 90, baseY - 50, texHandle[0], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		return;
	}

	if (time < 255)
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, time);
		DrawRotaGraph(110, baseY, 1.0, (300 - time) / 100.0, texHandle[0], TRUE, FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	if(time <= 750)
		DrawRotaGraph(110, baseY, 1.0, (300 - time) / 100.0, texHandle[0], TRUE, FALSE);
	else
		DrawGraph(time / 5 - 90, baseY - 50, texHandle[0], TRUE);

	if (time <= 510)
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255 - abs(time - 255));
		DrawExtendGraph(50, baseY - 60, 170, baseY + 60, texHandle[1], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

}

void Button::End()
{
	end = true;
}

int Button::GetTime() const
{
	return time;
}