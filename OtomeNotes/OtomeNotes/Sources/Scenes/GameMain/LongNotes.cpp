#include"LongNotes.h"
#include"../../MainController/InputController.h"


LongNotes::LongNotes(int _notesHandle, int _releaseTime,int _longNotesHandle[]) : Notes(_notesHandle)
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

	Dead = !push && (time > popToJustTime + 500);

}

void LongNotes::Draw(int centerX, int centerY) const 
{
	int rateS = static_cast<int>(80.0 * (1.0 - time / static_cast<double>(popToJustTime)));
	int rateE = static_cast<int>(80.0 * (1.0 - (time - releaseTime) / static_cast<double>(popToJustTime)));

	if (time < popToJustTime)
	{
		DrawExtendGraph(centerX - 70, centerY - 240, centerX + 70, centerY - rateS * 3, longNotesHandle[1], TRUE);
		DrawExtendGraph(centerX - 70, centerY - rateS * 3, centerX + 70, centerY - rateS * 3 + 70, longNotesHandle[2], TRUE);
	}
	else if (time < releaseTime)
	{
		DrawExtendGraph(centerX - 70, centerY - 240, centerX + 70, centerY, longNotesHandle[1], TRUE);
		DrawExtendGraph(centerX - 70, centerY, centerX + 70, centerY + 70, longNotesHandle[2], TRUE);
	}
	else if (time < releaseTime + popToJustTime)
	{
		DrawExtendGraph(centerX - 70, centerY - rateE * 3 - 70, centerX + 70, centerY - rateE * 3, longNotesHandle[0], TRUE);
		DrawExtendGraph(centerX - 70, centerY - rateE * 3, centerX + 70, centerY, longNotesHandle[1], TRUE);
		DrawExtendGraph(centerX - 70, centerY, centerX + 70, centerY + 70, longNotesHandle[2], TRUE);
	}

	if (!push)
	{
		DrawExtendGraph(centerX - 70 - rateS, centerY - 70 - rateS, centerX + 70 + rateS, centerY + 70 + rateS, notesHandle, TRUE);
	}
	else
	{
		DrawExtendGraph(centerX - 70 - rateE, centerY - 70 - rateE, centerX + 70 + rateE, centerY + 70 + rateE, notesHandle, TRUE);
	}
}

void LongNotes::Push()
{
	Dead = push;
	push = true;

	Evalution = EvalutionType::DEFAULT;
}