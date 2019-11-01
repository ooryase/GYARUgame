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

bool Notes::Update(int deltaTime , bool active)
{
	time += deltaTime;

	if (InputController::getInstance().GetPush(KEY_INPUT_SPACE) && active)
	{
		Evalution = NotesEvalution(time - popToJustTime);
		return false;
	}
	
	if (time > popToJustTime + 390)
	{
		Dead = true;
		Evalution = EvalutionType::MISS;
	}
	return active;
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
 	if (abs(justTime) < 75)
	{
		return EvalutionType::PERFECT;
	}
	else if (abs(justTime) < 175)
	{
 		return EvalutionType::GOOD;
	}
	else if (abs(justTime) < 390)
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

int Notes::GetX() const
{
	return x;
}