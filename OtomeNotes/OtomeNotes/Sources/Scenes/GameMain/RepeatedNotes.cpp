#include"RepeatedNotes.h"
#include"../../MainController/InputController.h"


RepeatedNotes::RepeatedNotes(int _notesHandle,int _krkrHandle,int _x,int _y, int _releaseTime,int _longNotesHandle) : Notes(_notesHandle,_krkrHandle,_x,_y),
	longNotesHandle(_longNotesHandle)
{
	releaseTime = _releaseTime;
}

void RepeatedNotes::Update(int deltaTime)
{
	time += deltaTime;

	if (popToJustTime < time && time < releaseTime + popToJustTime)
	{
		if (InputController::getInstance().GetPush(KEY_INPUT_Z))
			Evalution = EvalutionType::PERFECT;
	}

	if (releaseTime + popToJustTime < time)
	{
		Dead = true;
		//Evalution = EvalutionType::BAD;
	}
}

void RepeatedNotes::Draw() const
{
	if (time < 510)
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, time / 2);
		DrawExtendGraph(x, y - 50, x + releaseTime / 10, y + 50, longNotesHandle, TRUE);
		DrawGraph(x - 50, y - 50, notesHandle, TRUE);
		DrawGraph(x - 50 + releaseTime / 10, y - 50, notesHandle, TRUE);

		SetDrawBlendMode(DX_BLENDMODE_ADD, 255 - abs(255 - time));
		DrawExtendGraph(x - 60, y - 60, x + 60, y + 60, krkrHandle, TRUE);
		DrawExtendGraph(x - 60 + releaseTime / 10, y - 60, x + 60 + releaseTime / 10, y + 60, krkrHandle, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else
	{
		DrawExtendGraph(x, y - 50, x + releaseTime / 10, y + 50, longNotesHandle, TRUE);
		DrawGraph(x - 50, y - 50, notesHandle, TRUE);
		DrawGraph(x - 50 + releaseTime / 10, y - 50, notesHandle, TRUE);
	}
}

void RepeatedNotes::Push()
{
	push = true;
	Evalution = EvalutionType::DEFAULT;
}