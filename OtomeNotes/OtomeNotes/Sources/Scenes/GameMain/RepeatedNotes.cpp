#include"RepeatedNotes.h"
#include"../../MainController/InputController.h"


RepeatedNotes::RepeatedNotes(int _notesHandle,int _x,int _y, int _releaseTime,int _longNotesHandle) : Notes(_notesHandle,_x,_y),
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
	DrawExtendGraph(x, y - 50, x + releaseTime / 5, y + 50, longNotesHandle, TRUE);

	DrawGraph(x - 50, y - 50, notesHandle, TRUE);
	DrawGraph(x - 50 + releaseTime / 5, y - 50, notesHandle, TRUE);

}

void RepeatedNotes::Push()
{
	push = true;
	Evalution = EvalutionType::DEFAULT;
}