#include<iostream>
#include"DxLib.h"
#include"Title.h"
#include"../MainController/InputController.h"
#include"StageSelect.h"

Title::Title() : VirtualScene(),
	titleGraphHandle(LoadGraph("Assets/Textures/Title/Titlelogo.png")),
	backGraphHandle(LoadGraph("Assets/Textures/Title/Title.png")),
	backGraph2Handle(LoadGraph("Assets/Textures/Title/Title_back.png")),
	textGraphHandle(LoadGraph("Assets/Textures/Title/Space.png")),
	movieHandle(LoadGraph("Assets/Movies/gbf_mv_20170809.mp4")),
	bgmHandle(LoadSoundMem("Assets/Sounds/BGM/Title.mp3")),
	titleCallHandle(LoadSoundMem("Assets/Sounds/Voice/SystemVoice/titlecall3.mp3")),
	pushSeHandle(LoadSoundMem("Assets/Sounds/SE/start3.mp3"))
{
	phase = TitlePhaseList::START;
	movieSkip = false;

	PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP);

}

Title::~Title()
{
	StopSoundMem(bgmHandle);

	DeleteGraph(titleGraphHandle);
	DeleteGraph(backGraphHandle);
	DeleteGraph(backGraph2Handle);
	DeleteGraph(textGraphHandle);
	DeleteGraph(movieHandle);
	DeleteSoundMem(bgmHandle);
	DeleteSoundMem(titleCallHandle);
	DeleteSoundMem(pushSeHandle);
}

void Title::Update()
{
	time->TimeUpdate();

	switch (phase)
	{
	case TitlePhaseList::START:
		if (InputController::getInstance().GetPush(KEY_INPUT_SPACE))
		{
			//PlayMovieToGraph(movieHandle);
			//phase = TitlePhaseList::MOVIE;
			//time->Reset();
			phase = TitlePhaseList::DECISION;
			PlaySoundMem(pushSeHandle, DX_PLAYTYPE_BACK);
			PlaySoundMem(titleCallHandle, DX_PLAYTYPE_BACK);
			time2 = time->GetTimeCount();
			time->Reset();
		}
#if _DEBUG		
		else if (InputController::getInstance().GetPush(KEY_INPUT_BACK))
		{
			phase = TitlePhaseList::NEXT;
			nextScene = std::make_shared<StageSelect>();
		}
#endif
		break;
	case TitlePhaseList::MOVIE:
		if (GetMovieStateToGraph(movieHandle) != 1 || 
			(InputController::getInstance().GetPush(KEY_INPUT_SPACE) &&	movieSkip))
		{
			phase = TitlePhaseList::NEXT;
			nextScene = std::make_shared<StageSelect>();
		}

		if (!movieSkip)
		{
			if (movieSkip = InputController::getInstance().GetPush(KEY_INPUT_SPACE))
				time->Reset();
		}
		else
			if (time->GetTimeCount() > 5000)
				movieSkip = false;
		break;
	case TitlePhaseList::DECISION:
		time2 += time->GetDeltaTime();
		if(time->GetTimeCount() > 1510)
			nextScene = std::make_shared<StageSelect>();
		break;
	default:
		break;
	}
}

void Title::Draw() const
{
	switch (phase)
	{
	case TitlePhaseList::START:
		DrawTitle();
		break;
	case TitlePhaseList::MOVIE:
		DrawMovie();
		break;
	case TitlePhaseList::DECISION:
		DrawDecision();
		break;
	default:
		break;
	}
}

void Title::DrawTitle() const
{
	int x, y, c;
	GetScreenState(&x, &y, &c);



	int i = time->GetTimeCount() % 20480 / 16;
	DrawExtendGraph(i, 0, x + i, 290, backGraph2Handle, TRUE);
	DrawExtendGraph(i - x, 0, i, 290, backGraph2Handle, TRUE);

	DrawExtendGraph(0, 0, x, y, backGraphHandle, TRUE);
	DrawExtendGraph(0, 0, x, y, titleGraphHandle, TRUE);

	auto a = static_cast<int>((std::cos(time->GetTimeCount() / 150.0) + 1.0) * 255.0);
	a = (a > 255) ? 255 : a;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
	DrawExtendGraph(x/ 2 - 320,y - 150,x / 2 + 320,y - 50, textGraphHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (time->GetTimeCount() < 510)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - time->GetTimeCount() / 2);
		DrawBox(0,0,x,y, GetColor(255,255,255), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void Title::DrawMovie() const
{
	int x, y, c;
	GetScreenState(&x,&y,&c);
	DrawExtendGraph(0, 0, x, y, movieHandle, FALSE);

	if (movieSkip)
	{
		auto a = static_cast<int>((std::cos(time->GetTimeCount() / 150.0) + 1.0) * 255.0);
		a = (a > 255) ? 255 : a;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
		DrawExtendGraph(x / 2 - 400, y / 3 * 2, x / 2 + 400, y / 3 * 2 + 200, textGraphHandle, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	WaitTimer(17);

}

void Title::DrawDecision() const
{
	int x, y, c;
	GetScreenState(&x, &y, &c);


	int i = time2 % 20480 / 16;
	DrawExtendGraph(i, 0, x + i, 290, backGraph2Handle, TRUE);
	DrawExtendGraph(i - x, 0, i, 290, backGraph2Handle, TRUE);

	DrawExtendGraph(0, 0, x, y, backGraphHandle, TRUE);
	DrawExtendGraph(0, 0, x, y, titleGraphHandle, TRUE);

	auto a = time->GetTimeCount() % 200;
	a = (a >= 100) ? 255 : 0;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
	DrawExtendGraph(x / 2 - 320, y - 150, x / 2 + 320, y - 50, textGraphHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	if (time->GetTimeCount() > 1000)
	{
		if (time->GetTimeCount() < 1510)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (time->GetTimeCount() - 1000) / 2);
			DrawBox(0, 0, x, y, GetColor(255, 255, 255), TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else
			DrawBox(0, 0, x, y, GetColor(255, 255, 255), TRUE);
	}
}