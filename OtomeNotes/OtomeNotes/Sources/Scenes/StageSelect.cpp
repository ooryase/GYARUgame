#include<iostream>
#include"DxLib.h"
#include"StageSelect.h"
#include"../MainController/InputController.h"
#include"../MainController/GameData.h"
#include"GameMain.h"


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
	time->TimeUpdate();

	switch (rotatePhase)
	{
	case StageSelect::START:
		radian += time->GetDeltaTime() / 3000.0 * 2.0 * PI;
		if (time->GetTimeCount() > 3000)
		{
			radian = 2.0 * PI;
			rotatePhase = RoratePhase::STOP;
			time->Reset();
		}
		break;
	case StageSelect::ROTATE:
		RotateUpdate();
		break;
	case StageSelect::STOP:
		if (InputController::getInstance().GetPush(KEY_INPUT_Z))
		{
			rotatePhase = RoratePhase::DECISION;
			time->Reset();
		}
		if (time->GetTimeCount() > 4000)
		{
			rotatePhase = RoratePhase::ROTATE;
			time->Reset();
			selectStage = (selectStage + 1) % stageImageHandle.size();
		}
		break;
	case StageSelect::DECISION:
		if (time->GetTimeCount() > 3000)
		{
			nextScene = std::make_shared<GameMain>();
			GameData::getInstance().Stage = selectStage;
		}
		break;
	default:
		break;
	}

}

void StageSelect::RotateUpdate()
{
	radian += time->GetDeltaTime() * 0.001 * 2.0 * PI / static_cast<double>(stageImageHandle.size());
	if (time->GetTimeCount() > 1000)
	{
		radian = 0.0;
		rotatePhase = RoratePhase::STOP;
		time->Reset();
	}

}

void StageSelect::Draw() const
{
	auto size = static_cast<double>(stageImageHandle.size());
	int x, y, c;
	GetScreenState(&x, &y, &c);

#define SIH(num) stageImageHandle.at((selectStage + stageImageHandle.size() + num) % stageImageHandle.size())

	int a = static_cast<int>( 255.0 * time->GetTimeCount() / 1000.0);
	switch (rotatePhase)
	{
	case StageSelect::START:
		DrawString(250, 240 - 32, "ステージセレクト！！！な演出", GetColor(0,0,0));
		break;
	case StageSelect::ROTATE:
		if (time->GetTimeCount() < 500)
		{
			DrawExtendGraph(Perf(x, 15.0 + 70.0 * cos(radian + 2.0 / size * PI + 0.5 * PI)), Perf(y, 10.0 + 15.0 * sin(radian + 2.0 / size * PI + 0.5 * PI)),
				Perf(x, 85.0 + 70.0 * cos(radian + 2.0 / size * PI + 0.5 * PI)), Perf(y, 80.0 + 15.0 * sin(radian + 2.0 / size * PI + 0.5 * PI)), SIH(1), FALSE);
			DrawExtendGraph(Perf(x, 15.0 + 70.0 * cos(radian - 2.0 / size * PI + 0.5 * PI)), Perf(y, 10.0 + 15.0 * sin(radian - 2.0 / size * PI + 0.5 * PI)),
				Perf(x, 85.0 + 70.0 * cos(radian - 2.0 / size * PI + 0.5 * PI)), Perf(y, 80.0 + 15.0 * sin(radian - 2.0 / size * PI + 0.5 * PI)), SIH(0), FALSE);
			DrawExtendGraph(Perf(x, 15.0 + 70.0 * cos(radian + 0.5 * PI)), Perf(y, 10.0 + 15.0 * sin(radian + 0.5 * PI)),
				Perf(x, 85.0 + 70.0 * cos(radian + 0.5 * PI)), Perf(y, 80.0 + 15.0 * sin(radian + 0.5 * PI)), SIH(2), FALSE);
		}
		else
		{
			DrawExtendGraph(Perf(x, 15.0 + 70.0 * cos(radian + 2.0 / size * PI + 0.5 * PI)), Perf(y, 10.0 + 15.0 * sin(radian + 2.0 / size * PI + 0.5 * PI)),
				Perf(x, 85.0 + 70.0 * cos(radian + 2.0 / size * PI + 0.5 * PI)), Perf(y, 80.0 + 15.0 * sin(radian + 2.0 / size * PI + 0.5 * PI)), SIH(1), FALSE);
			DrawExtendGraph(Perf(x, 15.0 + 70.0 * cos(radian + 0.5 * PI)), Perf(y, 10.0 + 15.0 * sin(radian + 0.5 * PI)),
				Perf(x, 85.0 + 70.0 * cos(radian + 0.5 * PI)), Perf(y, 80.0 + 15.0 * sin(radian + 0.5 * PI)), SIH(2), FALSE);
			DrawExtendGraph(Perf(x, 15.0 + 70.0 * cos(radian - 2.0 / size * PI + 0.5 * PI)), Perf(y, 10.0 + 15.0 * sin(radian - 2.0 / size * PI + 0.5 * PI)),
				Perf(x, 85.0 + 70.0 * cos(radian - 2.0 / size * PI + 0.5 * PI)), Perf(y, 80.0 + 15.0 * sin(radian - 2.0 / size * PI + 0.5 * PI)), SIH(0), FALSE);
		}
		break;
	case StageSelect::STOP:
		DrawExtendGraph(Perf(x, 15.0 + 70.0 * cos(radian + 2.0 / size * PI + 0.5 * PI)),	Perf(y, 10.0 + 15.0 * sin(radian + 2.0 / size * PI + 0.5 * PI)),
			            Perf(x, 85.0 + 70.0 * cos(radian + 2.0 / size * PI + 0.5 * PI)),	Perf(y, 80.0 + 15.0 * sin(radian + 2.0 / size * PI + 0.5 * PI)), SIH(2), FALSE);
		DrawExtendGraph(Perf(x, 15.0 + 70.0 * cos(radian - 2.0 / size * PI + 0.5 * PI)),	Perf(y, 10.0 + 15.0 * sin(radian - 2.0 / size * PI + 0.5 * PI)),
						Perf(x, 85.0 + 70.0 * cos(radian - 2.0 / size * PI + 0.5 * PI)),	Perf(y, 80.0 + 15.0 * sin(radian - 2.0 / size * PI + 0.5 * PI)), SIH(1), FALSE);
		DrawExtendGraph(Perf(x, 15.0 + 70.0 * cos(radian + 0.5 * PI)),	Perf(y, 10.0 + 15.0 * sin(radian + 0.5 * PI)),
						Perf(x, 85.0 + 70.0 * cos(radian + 0.5 * PI)),	Perf(y, 80.0 + 15.0 * sin(radian + 0.5 * PI)), SIH(0), FALSE);
		break;
	case StageSelect::DECISION:
		DrawExtendGraph(0, 0, x, y, stageImageHandle.at(selectStage), FALSE);
		if (time->GetTimeCount() < 1000)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
			DrawExtendGraph(static_cast<int>(- a * 16 / 20.0),static_cast<int>( - a * 9 / 20.0), x + static_cast<int>(a * 16 / 20.0), y + static_cast<int>(a * 9 / 20.0), stageImageHandle.at(selectStage), FALSE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		break;
	default:
		break;
	}
}

int StageSelect::Perf(int i, double perf) const
{
	return static_cast<int>(i / 100.0 * perf);
}