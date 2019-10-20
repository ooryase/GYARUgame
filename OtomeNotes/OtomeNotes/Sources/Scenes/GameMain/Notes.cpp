#include"Notes.h"
#include"../../MainController/InputController.h"

Notes::Notes(NotesType _notesType,int _notesHandle) :
	notesHandle(_notesHandle)
{
	time = 0;
	notesType = _notesType;
	Evalution = EvalutionType::DEFAULT;

	Dead = false;
}

void Notes::Update(int deltaTime)
{
	time += deltaTime;

	if (InputController::getInstance().GetPush(KEY_INPUT_Z))
	{

		if (abs(time - 600) < 50)
		{
			Evalution = EvalutionType::PERFECT;
		}
		else if (abs(time - 600) < 250)
		{
			Evalution = EvalutionType::GOOD;
		}
		else if (abs(time - 600) < 300)
		{
			Evalution = EvalutionType::BAD;
		}
	}
	
	Dead = (time > 1200);
}

void Notes::Draw(int centerX,int centerY) const
{
	int rate = static_cast<int>(60.0 * (1.0 - time / 600.0));
	printfDx("%d\n", rate);
	DrawExtendGraph(centerX - 70 - rate, centerY - 70 - rate, centerX + 70 + rate, centerY + 70 + rate, notesHandle, TRUE);


}