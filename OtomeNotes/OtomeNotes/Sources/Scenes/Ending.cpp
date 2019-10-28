#include<iostream>
#include"DxLib.h"
#include"Ending.h"
#include"../MainController/InputController.h"
#include"Title.h"

Ending::Ending() : VirtualScene(),
backGraphHandle(LoadGraph("Assets/Textures/Title/Title_back.png")),
textGraphHandle(LoadGraph("Assets/Textures/Title/Space.png")),
endCallHandle(LoadSoundMem("Assets/Sounds/Voice/SystemVoice/titlecall3.mp3"))
{
	phase = PhaseList::START;
	time->Reset();
}

Ending::~Ending()
{
	DeleteGraph(backGraphHandle);
	DeleteGraph(textGraphHandle);
	DeleteSoundMem(endCallHandle);
}

void Ending::Update()
{
	time->TimeUpdate();

	switch (phase)
	{
	case PhaseList::START:
		if ((time->GetTimeCount() > 2000 && InputController::getInstance().GetPush(KEY_INPUT_Z)) ||
			time->GetTimeCount() > 10000)
		{
			phase = PhaseList::NEXT;
			time->Reset();
		}
#if _DEBUG		
		else if (InputController::getInstance().GetPush(KEY_INPUT_BACK))
		{
			phase = PhaseList::NEXT;
			nextScene = std::make_shared<Title>();
		}
#endif
		break;
	case PhaseList::NEXT:
		if(time->GetTimeCount() > 510)
			nextScene = std::make_shared<Title>();
		break;
	default:
		break;
	}
}

void Ending::Draw() const
{
	int x, y, c;
	GetScreenState(&x, &y, &c);

	switch (phase)
	{
	case PhaseList::START:
		DrawExtendGraph(0, 0, x, y, backGraphHandle, TRUE);
		if (time->GetTimeCount() < 510)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - time->GetTimeCount() / 2);
			DrawBox(0, 0, x, y, GetColor(255, 255, 255), TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}

		break;
	case PhaseList::NEXT:
		if (time->GetTimeCount() < 510)
		{
			DrawExtendGraph(0, 0, x, y, backGraphHandle, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, time->GetTimeCount() / 2);
			DrawBox(0, 0, x, y, GetColor(255, 255, 255), TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else
			DrawBox(0, 0, x, y, GetColor(255, 255, 255), TRUE);

		break;
	default:
		break;
	}
}