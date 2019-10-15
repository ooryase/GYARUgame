#include<iostream>
#include"DxLib.h"
#include"StageSelect.h"
#include"../MainController/InputController.h"
#include"Title.h"


StageSelect::StageSelect() : VirtualScene(),
	PI(3.14159265358979323846)
{
	stageImageHandle.push_back(LoadGraph("Assets/Textures/StageSelect/Stage1.jpg"));
	stageImageHandle.push_back(LoadGraph("Assets/Textures/StageSelect/Stage2.jpg"));
	stageImageHandle.push_back(LoadGraph("Assets/Textures/StageSelect/Stage3.jpg"));

	radian = 0.0;
	selectStage = 0;
	rotatePhase = RoratePhase::START;
}

StageSelect::~StageSelect()
{
	for (auto s : stageImageHandle)
	{
		DeleteGraph(s);
	}
}

void StageSelect::Update()
{
	time.TimeUpdate();

	switch (rotatePhase)
	{
	case StageSelect::START:
		radian += time.GetDeltaTime() / 3000.0 * 2.0 * PI;
		if (time.GetTimeCount() > 3000)
		{
			radian = 2.0 * PI;
			rotatePhase = RoratePhase::STOP;
			time.Reset();
		}
		break;
	case StageSelect::ROTATE:
		radian += time.GetDeltaTime() * 0.001 * 2.0 * PI / 3.0;
		if (time.GetTimeCount() > 1000)
		{
			radian = 2.0 * PI * selectStage / static_cast<double>( stageImageHandle.size());
			rotatePhase = RoratePhase::STOP;
			time.Reset();
		}
		break;
	case StageSelect::STOP:
		if (InputController::getInstance().GetPush(KEY_INPUT_Z))
		{
			rotatePhase = RoratePhase::DECISION;
			time.Reset();
		}
		if (time.GetTimeCount() > 5000)
		{
			rotatePhase = RoratePhase::ROTATE;
			time.Reset();
			selectStage = (selectStage + 1) % stageImageHandle.size();
		}
		break;
	case StageSelect::DECISION:
		if (time.GetTimeCount() > 3000)
		{
			nextScene = std::make_shared<Title>();
		}
		break;
	default:
		break;
	}

}

void StageSelect::Draw() const
{
	auto size = static_cast<double>(stageImageHandle.size());
	int x, y, c;
	GetScreenState(&x, &y, &c);

	/*for (int i = 0; i < size; i++)
	{

		DrawGraph( x / 2 + static_cast<int>( (x / 4) * std::cos(radian + 2.0 * PI * (i / size) + PI * 0.5)) - 150,
			y / 2 + static_cast<int>( (y / 8) * std::sin(radian + 2.0 * PI * (i / size) + PI * 0.5)) - 230,
			stageImageHandle.at(i), TRUE);
	}*/
	auto delta = static_cast<int>(time.GetTimeCount() * x / 1000.0);

	int a = 255 * time.GetTimeCount() / 1000.0;
	switch (rotatePhase)
	{
	case StageSelect::START:
		DrawString(250, 240 - 32, "ステージセレクト！！！な演出", GetColor(0,0,0));
		break;
	case StageSelect::ROTATE:
		DrawExtendGraph(64 + x - delta, 36, 2 * x - 64 - delta, y - 36, stageImageHandle.at(selectStage), FALSE);
		DrawExtendGraph(64 - delta, 36, x - 64 - delta, y - 36, stageImageHandle.at((selectStage + stageImageHandle.size() - 1) % stageImageHandle.size()), FALSE);

		break;
	case StageSelect::STOP:
		DrawExtendGraph(64, 36, x - 64, y - 36, stageImageHandle.at(selectStage), FALSE);
		break;
	case StageSelect::DECISION:
		DrawExtendGraph(64, 36, x - 64, y - 36, stageImageHandle.at(selectStage), FALSE);
		if (time.GetTimeCount() < 1000)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
			DrawExtendGraph(64 - a * 16 / 20.0, 36 - a * 9 / 20.0, x - 64 + a * 16 / 20.0, y - 36 + a * 9 / 20.0, stageImageHandle.at(selectStage), FALSE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		break;
	default:
		break;
	}
}