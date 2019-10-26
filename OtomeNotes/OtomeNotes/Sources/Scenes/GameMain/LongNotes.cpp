#include"LongNotes.h"
#include"../../MainController/InputController.h"


LongNotes::LongNotes(int _notesHandle,int _x,int _y, int _releaseTime,int _longNotesHandle[]) : Notes(_notesHandle,_x,_y)
{
	memcpy(longNotesHandle, _longNotesHandle, sizeof(longNotesHandle));
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

	if (!push && (time > popToJustTime + 500))
	{
		Dead = true;
		Evalution = EvalutionType::BAD;
	}

}

void LongNotes::Draw() const 
{
	/*int rateS = static_cast<int>(80.0 * (1.0 - time / static_cast<double>(popToJustTime)));
	int rateE = static_cast<int>(80.0 * (1.0 - (time - releaseTime) / static_cast<double>(popToJustTime)));

	if (time < popToJustTime)
	{
		DrawExtendGraph(x - 50, y - 400, x + 50, y - rateS * 5, longNotesHandle[1], TRUE);
		DrawExtendGraph(x - 50, y - rateS * 5, x + 50, y - rateS * 5 + 50, longNotesHandle[2], TRUE);
	}
	else if (time < releaseTime)
	{
		DrawExtendGraph(x - 50, y - 400, x + 50, y, longNotesHandle[1], TRUE);
		DrawExtendGraph(x - 50, y, x + 50, y + 50, longNotesHandle[2], TRUE);
	}
	else if (time < releaseTime + popToJustTime)
	{
		DrawExtendGraph(x - 50, y - rateE * 5 - 50, x + 50, y - rateE * 5, longNotesHandle[0], TRUE);
		DrawExtendGraph(x - 50, y - rateE * 5, x + 50, y, longNotesHandle[1], TRUE);
		DrawExtendGraph(x - 50, y, x + 50, y + 50, longNotesHandle[2], TRUE);
	}

	if (!push)
	{
		DrawExtendGraph(x - 50 - rateS, y - 50 - rateS, x + 50 + rateS, y + 50 + rateS, notesHandle, TRUE);
	}
	else
	{
		DrawExtendGraph(x - 50 - rateE, y - 50 - rateE, x + 50 + rateE, y + 50 + rateE, notesHandle, TRUE);
	}*/

	DrawExtendGraph(x, y - 50, x + releaseTime / 10, y + 50, longNotesHandle[1], TRUE);

	DrawExtendGraph(x - 50, y - 50, x + 50, y + 50, notesHandle, TRUE);
	DrawExtendGraph(x - 50 + releaseTime / 10, y - 50, x + 50 + releaseTime / 10, y + 50, notesHandle, TRUE);

}

void LongNotes::Push()
{
	Dead = push;
	push = true;

	Evalution = EvalutionType::DEFAULT;
}