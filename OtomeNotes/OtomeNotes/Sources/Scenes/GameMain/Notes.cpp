#include"Notes.h"
#include"../../MainController/InputController.h"

Notes::Notes(int _notesHandle) :
	notesHandle(_notesHandle)
{
	time = 0;
	popToJustTime = 1000;
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
	
	Dead = (time > popToJustTime + 300);
}

void Notes::Draw(int centerX,int centerY) const
{
	int rate = static_cast<int>(80.0 * (1.0 - time / static_cast<double>(popToJustTime)));
	DrawExtendGraph(centerX - 70 - rate, centerY - 70 - rate, centerX + 70 + rate, centerY + 70 + rate, notesHandle, TRUE);


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