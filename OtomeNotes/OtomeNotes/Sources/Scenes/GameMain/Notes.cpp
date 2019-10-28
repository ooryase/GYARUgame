#include"Notes.h"
#include"../../MainController/InputController.h"

Notes::Notes(int _notesHandle,int _krkrHandle, int _x, int _y) :
	notesHandle(_notesHandle),
	krkrHandle(_krkrHandle),
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
	if (time < 510)
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, time / 2);
		DrawGraph(x - 50, y - 50, notesHandle, TRUE);


		SetDrawBlendMode(DX_BLENDMODE_ADD, 255 - abs(255 - time));
		DrawExtendGraph(x - 60, y - 60, x + 60, y + 60, krkrHandle, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else
		DrawGraph(x - 50, y - 50, notesHandle, TRUE);
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