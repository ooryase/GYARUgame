#include"DxLib.h"
#include"Button.h"

Button::Button(int _texHandle, int _popToJustTime) :
	texHandle(_texHandle),
	baseX(200),
	baseY(500),
	notesPopToJustTime(_popToJustTime)
{
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
		
		Dead = (endTimer > 1200);
	}
}

void Button::Draw() const
{
	DrawExtendGraph(time / 10 + 30, baseY - 50, time / 10 + 130, baseY + 50, texHandle, TRUE);
}

void Button::End()
{
	end = true;
}

int Button::GetTime() const
{
	return time;
}