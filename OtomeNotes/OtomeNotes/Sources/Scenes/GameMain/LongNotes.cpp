#include"LongNotes.h"
#include"../../MainController/InputController.h"


LongNotes::LongNotes(int _notesHandle,int _krkrHandle,int _x,int _y, int _releaseTime,int _longNotesHandle) : Notes(_notesHandle,_krkrHandle,_x,_y),
longNotesHandle(_longNotesHandle)
{
	releaseTime = _releaseTime;
}

bool LongNotes::Update(int deltaTime,bool active)
{
	time += deltaTime;

	if (!push && InputController::getInstance().GetPush(KEY_INPUT_SPACE) && active)
	{
 		Evalution = NotesEvalution(time - popToJustTime);
		return false;
	}
	else if (push && InputController::getInstance().GetRelease(KEY_INPUT_SPACE) && active)
	{
		Evalution = NotesEvalution(time - (popToJustTime + releaseTime));
		Evalution = (Evalution == EvalutionType::DEFAULT) ? EvalutionType::MISS : Evalution;
		return false;
	}

	if ((!push && time > popToJustTime + 500) ||
		(push && time > popToJustTime + 500 + releaseTime))
	{
		Dead = true;
		Evalution = EvalutionType::MISS;
	}
	return active;

}

void LongNotes::Draw() const 
{
	if (time < 510)
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, time / 2);
		DrawExtendGraph(x, y - 50, x + releaseTime / 5, y + 50, longNotesHandle, TRUE);
		DrawGraph(x - 50, y - 50, notesHandle, TRUE);
		DrawGraph(x - 50 + releaseTime / 5, y - 50, notesHandle, TRUE);

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
	}
}

void LongNotes::Push()
{
	Dead = (Evalution == EvalutionType::MISS) || push;
	push = true;

	Evalution = EvalutionType::DEFAULT;
}