#include<iostream>
#include"DxLib.h"
#include"Title.h"
#include"../MainController/InputController.h"
#include"StageSelect.h"

Title::Title() : VirtualScene(),
	titleGraphHandle(LoadGraph("Assets/Textures/Title/Title.jpg")),
	textGraphHandle(LoadGraph("Assets/Textures/Title/ChargePlease.png")),
	movieHandle(LoadGraph("Assets/Movies/gbf_mv_20170809.mp4"))
{
	phase = TitlePhaseList::START;
	movieSkip = false;
}

Title::~Title()
{
	DeleteGraph(titleGraphHandle);
	DeleteGraph(movieHandle);
}

void Title::Update()
{
	time.TimeUpdate();

	switch (phase)
	{
	case TitlePhaseList::START:
		if (InputController::getInstance().GetPush(KEY_INPUT_Z))
		{
			PlayMovieToGraph(movieHandle);
			phase = TitlePhaseList::MOVIE;
			time.Reset();
		}
		break;
	case TitlePhaseList::MOVIE:
		if (GetMovieStateToGraph(movieHandle) != 1 || 
			(InputController::getInstance().GetPush(KEY_INPUT_Z) &&	movieSkip))
		{
			phase = TitlePhaseList::NEXT;
			nextScene = std::make_shared<StageSelect>();
		}

		if (!movieSkip)
		{
			if (movieSkip = InputController::getInstance().GetPush(KEY_INPUT_Z))
				time.Reset();
		}
		else
			if (time.GetTimeCount() > 5000)
				movieSkip = false;
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
	default:
		break;
	}

	printfDx("%d \n", time.GetTimeCount());
}

void Title::DrawTitle() const
{
	int x, y, c;
	GetScreenState(&x, &y, &c);


	DrawExtendGraph(300, 0, x - 300, y, titleGraphHandle, TRUE);

	auto a = static_cast<int>((std::cos(time.GetTimeCount() / 150.0) + 1.0) * 255.0);
	a = (a > 255) ? 255 : a;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
	DrawExtendGraph(x / 2 - 400, y / 3 * 2, x / 2 + 400, y / 3 * 2 + 200, textGraphHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Title::DrawMovie() const
{
	int x, y, c;
	GetScreenState(&x,&y,&c);
	DrawExtendGraph(0, 0, x, y, movieHandle, FALSE);

	if (movieSkip)
	{
		auto a = static_cast<int>((std::cos(time.GetTimeCount() / 150.0) + 1.0) * 255.0);
		a = (a > 255) ? 255 : a;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
		DrawExtendGraph(x / 2 - 400, y / 3 * 2, x / 2 + 400, y / 3 * 2 + 200, textGraphHandle, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	// ウエイトをかけます、あまり速く描画すると画面がちらつくからです
	WaitTimer(17);

}