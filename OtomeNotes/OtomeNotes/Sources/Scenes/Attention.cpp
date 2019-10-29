#include"DxLib.h"
#include"Attention.h"
#include"Title.h"
#include"../MainController/InputController.h"

Attention::Attention() : VirtualScene(),
texHandle(LoadGraph("Assets/Textures/Attention/Attention.png"))
{
	phase = PhaseList::START;
}

Attention::~Attention()
{
	DeleteGraph(texHandle);
}

void Attention::Update()
{
	time->TimeUpdate();

	switch (phase)
	{
	case Attention::START:
		if (time->GetTimeCount() > 10000 ||
			time->GetTimeCount() > 1000 && InputController::getInstance().GetPush(KEY_INPUT_SPACE))
		{
			phase = PhaseList::NEXT;
			time->Reset();
		}
		break;
	case Attention::NEXT:
		if (time->GetTimeCount() > 510)
			nextScene = std::make_shared<Title>();
		break;
	default:
		break;
	}
}


void Attention::Draw() const
{
	int x, y, c;
	GetScreenState(&x, &y, &c);

	switch (phase)
	{
	case Attention::START:
		if (time->GetTimeCount() < 510)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, time->GetTimeCount() / 2);
			DrawExtendGraph(0, 0, x, y, texHandle, FALSE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else
			DrawExtendGraph(0, 0, x, y, texHandle, FALSE);

		break;
	case Attention::NEXT:
		if (time->GetTimeCount() < 510)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - time->GetTimeCount() / 2);
			DrawExtendGraph(0, 0, x, y, texHandle, FALSE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
			
		break;
	default:
		break;
	}
}