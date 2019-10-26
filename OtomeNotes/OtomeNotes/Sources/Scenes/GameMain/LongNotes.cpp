#include"LongNotes.h"
#include"../../MainController/InputController.h"


LongNotes::LongNotes(int _notesHandle,int _x,int _y, int _releaseTime,int _longNotesHandle) : Notes(_notesHandle,_x,_y),
longNotesHandle(_longNotesHandle)
{
	releaseTime = _releaseTime;
}

void LongNotes::Update(int deltaTime)
{
	time += deltaTime;

	if (!push && InputController::getInstance().GetPush(KEY_INPUT_Z))
	{
		Evalution = NotesEvalution(time - popToJustTime);
	}
	else if (push && InputController::getInstance().GetRelease(KEY_INPUT_Z))
	{
		Evalution = NotesEvalution(time - (popToJustTime + releaseTime));
		Evalution = (Evalution == EvalutionType::DEFAULT) ? EvalutionType::BAD : Evalution;
	}

	if ((!push && time > popToJustTime + 500) ||
		(push && time > popToJustTime + 500 + releaseTime))
	{
		Dead = true;
		Evalution = EvalutionType::BAD;
	}

}

void LongNotes::Draw() const 
{
	DrawExtendGraph(x, y - 50, x + releaseTime / 10, y + 50, longNotesHandle, TRUE);

	DrawExtendGraph(x - 50, y - 50, x + 50, y + 50, notesHandle, TRUE);
	DrawExtendGraph(x - 50 + releaseTime / 10, y - 50, x + 50 + releaseTime / 10, y + 50, notesHandle, TRUE);

}

void LongNotes::Push()
{
	Dead = (Evalution == EvalutionType::BAD) || push;
	push = true;

	Evalution = EvalutionType::DEFAULT;
}