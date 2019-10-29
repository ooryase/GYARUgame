#include"RepeatedNotes.h"
#include"../../MainController/InputController.h"


RepeatedNotes::RepeatedNotes(int _notesHandle,int _krkrHandle,int _x,int _y, int _releaseTime,int _longNotesHandle,int _fontHandle) : Notes(_notesHandle,_krkrHandle,_x,_y),
	longNotesHandle(_longNotesHandle),
	fontHandle(_fontHandle)
{
	releaseTime = _releaseTime;
}

bool RepeatedNotes::Update(int deltaTime,bool active)
{
	time += deltaTime;

	if (InputController::getInstance().GetPush(KEY_INPUT_SPACE) && active)
	{
		if (popToJustTime - 75 < time && time < releaseTime + popToJustTime + 75)
		{
			Evalution = EvalutionType::PERFECT;
			return false;
		}
		else if (popToJustTime - 175 < time && time < releaseTime + popToJustTime + 175)
		{
			Evalution = EvalutionType::GOOD;
			return false;
		}
		else if (popToJustTime - 390 < time && time < releaseTime + popToJustTime + 390)
		{
			Evalution = EvalutionType::BAD;
			return false;
		}
	}

	if (releaseTime + popToJustTime < time)
	{
		Dead = true;
		//Evalution = EvalutionType::BAD;
	}
	return active;
}

void RepeatedNotes::Draw() const
{
	if (time < 510)
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, time / 2);
		DrawExtendGraph(x, y - 50, x + releaseTime / 5, y + 50, longNotesHandle, TRUE);
		DrawGraph(x - 50, y - 50, notesHandle, TRUE);
		DrawGraph(x - 50 + releaseTime / 5, y - 50, notesHandle, TRUE);
		DrawStringToHandle(x + releaseTime / 10 - 32,y - 80,"˜A‘Å",GetColor(255, 225, 195),fontHandle);

		SetDrawBlendMode(DX_BLENDMODE_ADD, 255 - abs(255 - time));
		DrawExtendGraph(x - 60, y - 60, x + 60, y + 60, krkrHandle, TRUE);
		DrawExtendGraph(x - 60 + releaseTime / 5, y - 60, x + 60 + releaseTime / 5, y + 60, krkrHandle, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else
	{
		DrawExtendGraph(x, y - 50, x + releaseTime / 5, y + 50, longNotesHandle, TRUE);
		DrawGraph(x - 50, y - 50, notesHandle, TRUE);
		DrawGraph(x - 50 + releaseTime / 5, y - 50, notesHandle, TRUE);
		DrawStringToHandle(x + releaseTime / 10 - 32, y - 80, "˜A‘Å", GetColor(255, 225, 195), fontHandle);
	}
}

void RepeatedNotes::Push()
{
	push = true;
	Evalution = EvalutionType::DEFAULT;
}