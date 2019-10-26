#include"Notes.h"
#include"../../MainController/InputController.h"

Notes::Notes(int _notesHandle,int _x, int _y) :
	notesHandle(_notesHandle),
	x(_x),
	y(_y)
{
	time = 0;
	popToJustTime = 1200;
	Evalution = EvalutionType::DEFAULT;

	Dead = false;
	push = false;
}

void Notes::Update(int deltaTime)
{
	time += deltaTime;

	if (InputController::getInstance().GetPush(KEY_INPUT_Z))
	{
		Evalution = NotesEvalution(time - popToJustTime);
	}
	
	if (time > popToJustTime + 300)
	{
		Dead = true;
		Evalution = EvalutionType::BAD;
	}
}

void Notes::Draw() const
{
	/*int rateS = static_cast<int>(80.0 * (1.0 - time / static_cast<double>(popToJustTime)));

	DrawExtendGraph(x - 50, y - 50 - rateS * 5, x + 50, y  + 50 - rateS * 5, notesHandle, TRUE);



	int rate = static_cast<int>(80.0 * (1.0 - time / static_cast<double>(popToJustTime)));
	DrawExtendGraph(x - 50 - rate, y - 50 - rate, x + 50 + rate, y + 50 + rate, notesHandle, TRUE);
	*/
	DrawExtendGraph(x - 50, y - 50, x + 50, y + 50, notesHandle, TRUE);

}

Notes::EvalutionType Notes::NotesEvalution(int justTime)
{
	if (abs(justTime) < 50)
	{
		return EvalutionType::PERFECT;
	}
	else if (abs(justTime) < 250)
	{
		return EvalutionType::GOOD;
	}
	else if (abs(justTime) < 300)
	{
		return EvalutionType::BAD;
	}
	else
		return EvalutionType::DEFAULT;
}

void Notes::Push()
{
	Dead = true;
	Evalution = EvalutionType::DEFAULT;
}