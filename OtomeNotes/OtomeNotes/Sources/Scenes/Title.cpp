#include<iostream>
#include"DxLib.h"
#include"Title.h"

Title::Title() : VirtualScene(),
	titleGraphHandle(LoadGraph("Assets/Textures/Title/Title.jpg")),
	textGraphHandle(LoadGraph("Assets/Textures/Title/ChargePlease.png")),
	movieHandle(LoadGraph("Assets/Movies/gbf_mv_20170809.mp4"))
{
	phase = TitlePhaseList::START;
}

Title::~Title()
{
	DeleteGraph(titleGraphHandle);
	DeleteGraph(movieHandle);
}

void Title::Update()
{
	switch (phase)
	{
	case TitlePhaseList::START:
		if (CheckHitKeyAll())
		{
			PlayMovieToGraph(movieHandle);
			phase = TitlePhaseList::MOVIE;
		}
		break;
	case TitlePhaseList::MOVIE:
		if (GetMovieStateToGraph(movieHandle) != 1 || CheckHitKey(KEY_INPUT_Z))
		{
			phase = TitlePhaseList::NEXT;
			nextScene = std::make_shared<Title>();
		}
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
}

void Title::DrawTitle() const
{
	int x, y, c;
	GetScreenState(&x, &y, &c);


	DrawExtendGraph(300, 0, x - 300, y, titleGraphHandle, TRUE);

	auto a = static_cast<int>((std::cos(GetNowCount() / 150.0) + 1.0) * 255.0);
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

	// ウエイトをかけます、あまり速く描画すると画面がちらつくからです
	WaitTimer(17);

}