#include"RepeatedNotes.h"
#include"../../MainController/InputController.h"


RepeatedNotes::RepeatedNotes(int _notesHandle,int _x,int _y, int _releaseTime,int _longNotesHandle[]) : Notes(_notesHandle,_x,_y)
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

	if (releaseTime + popToJustTime < time)
	{
		Dead = true;
		//Evalution = EvalutionType::BAD;
	}

}

void RepeatedNotes::Draw() const
{
	/*int rateS = static_cast<int>(80.0 * (1.0 - time / static_cast<double>(popToJustTime)));
	int rateE = static_cast<int>(80.0 * (1.0 - (time - releaseTime) / static_cast<double>(popToJustTime)));

	int size = 50;
	if (time < popToJustTime)
	{
		DrawExtendGraph(x - size, y - 400, x + size, y - rateS * 5, longNotesHandle[1], TRUE);
		DrawExtendGraph(x - size, y - rateS * 5, x + size, y - rateS * 5 + size, longNotesHandle[2], TRUE);
	}
	else if (time < releaseTime)
	{
		DrawExtendGraph(x - size, y - 400, x + size, y, longNotesHandle[1], TRUE);
		DrawExtendGraph(x - size, y, x + size, y + size, longNotesHandle[2], TRUE);
	}
	else if (time < releaseTime + popToJustTime)
	{
		DrawExtendGraph(x - size, y - rateE * 5 - size, x + size, y - rateE * 5, longNotesHandle[0], TRUE);
		DrawExtendGraph(x - size, y - rateE * 5, x + size, y, longNotesHandle[1], TRUE);
		DrawExtendGraph(x - size, y, x + size, y + size, longNotesHandle[2], TRUE);
	}

	if (time < popToJustTime + 500)
	{
		int rate = static_cast<int>(80.0 * (1.0 - time / static_cast<double>(popToJustTime)));
		DrawExtendGraph(x - size - rate, y - size - rate, x + size + rate, y + size + rate, notesHandle, TRUE);
	}
	else if(releaseTime - popToJustTime < time && time < releaseTime + popToJustTime)
	{
		int rate = static_cast<int>(80.0 * (1.0 - (time - releaseTime) / static_cast<double>(popToJustTime)));
		DrawExtendGraph(x - size - rate, y - size - rate, x + size + rate, y + size + rate, notesHandle, TRUE);
	}*/

	DrawExtendGraph(x, y - 50, x + releaseTime / 10, y + 50, longNotesHandle[1], TRUE);

	DrawExtendGraph(x - 50, y - 50, x + 50, y + 50, notesHandle, TRUE);
	DrawExtendGraph(x - 50 + releaseTime / 10, y - 50, x + 50 + releaseTime / 10, y + 50, notesHandle, TRUE);

}

void RepeatedNotes::Push()
{
	push = true;
	Evalution = EvalutionType::DEFAULT;
}