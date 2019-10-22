#include"RepeatedNotes.h"
#include"../../MainController/InputController.h"


RepeatedNotes::RepeatedNotes(int _notesHandle, int _releaseTime,int _longNotesHandle[]) : Notes(_notesHandle)
{
	memcpy(longNotesHandle, _longNotesHandle, sizeof(longNotesHandle));
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

	Dead = (releaseTime + popToJustTime < time);

}

void RepeatedNotes::Draw(int centerX, int centerY) const
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

	if (time < popToJustTime + 500)
	{
		int rate = static_cast<int>(80.0 * (1.0 - time / static_cast<double>(popToJustTime)));
		DrawExtendGraph(centerX - 70 - rate, centerY - 70 - rate, centerX + 70 + rate, centerY + 70 + rate, notesHandle, TRUE);
	}
	else if(releaseTime - popToJustTime < time && time < releaseTime + popToJustTime)
	{
		int rate = static_cast<int>(80.0 * (1.0 - (time - releaseTime) / static_cast<double>(popToJustTime)));
		DrawExtendGraph(centerX - 70 - rate, centerY - 70 - rate, centerX + 70 + rate, centerY + 70 + rate, notesHandle, TRUE);
	}
}

void RepeatedNotes::Push()
{
	push = true;
	Evalution = EvalutionType::DEFAULT;
}