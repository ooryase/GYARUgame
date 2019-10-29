#include<iostream>
#include"DxLib.h"
#include"StageSelect.h"
#include"../MainController/InputController.h"
#include"../MainController/GameData.h"
#include"GameMain.h"


StageSelect::StageSelect() : VirtualScene(),
	PI(3.14159265358979323846),
	backGraphHandle(LoadGraph("Assets/Textures/StageSelect/Back.png")),
	infoVoiceHandle(LoadSoundMem("Assets/Sounds/Voice/SystemVoice/situation1.mp3")),
	bgmHandle(LoadSoundMem("Assets/Sounds/BGM/StageSelect.mp3")),
	pushSeHandle(LoadSoundMem("Assets/Sounds/SE/start3.mp3")),
	fontHandle(LoadFontDataToHandle("Assets/Fonts/Senobi_m.dft", 1))
{
	stageImageHandle.push_back(std::make_pair(LoadGraph("Assets/Textures/StageSelect/Stage1.jpg"),
		LoadGraph("Assets/Textures/StageSelect/font1.png")));
	stageImageHandle.push_back(std::make_pair(LoadGraph("Assets/Textures/StageSelect/Stage2.jpg"),
		LoadGraph("Assets/Textures/StageSelect/font2.png")));
	stageImageHandle.push_back(std::make_pair(LoadGraph("Assets/Textures/StageSelect/Stage3.jpg"),
		LoadGraph("Assets/Textures/StageSelect/font3.png")));
	LoadDivGraph("Assets/Textures/GameMain/FullTexture.png", 1, 1, 1, 640, 360, &loadHandle);

	radian = 0.0;
	selectStage = 0;
	rotatePhase = RoratePhase::START;

	pressTime = 0;
	PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP);

}

StageSelect::~StageSelect()
{
	for (auto s : stageImageHandle)
	{
		DeleteGraph(s.first);
		DeleteGraph(s.second);
	}

	DeleteGraph(backGraphHandle);

	StopSoundMem(bgmHandle);
	DeleteSoundMem(bgmHandle);
	DeleteSoundMem(infoVoiceHandle);
	DeleteSoundMem(pushSeHandle);
	DeleteFontToHandle(fontHandle);
}

void StageSelect::Update()
{
	time->TimeUpdate();

	switch (rotatePhase)
	{
	case StageSelect::START:
		//radian += time->GetDeltaTime() / 3000.0 * 2.0 * PI;
		if (time->GetTimeCount() > 510)
		{
			PlaySoundMem(infoVoiceHandle, DX_PLAYTYPE_BACK);
			radian = 2.0 * PI;
			rotatePhase = RoratePhase::STOP;
			time->Reset();
		}
		break;
	case StageSelect::ROTATE:
		RotateUpdate();
		break;
	case StageSelect::STOP:
		/*if (InputController::getInstance().GetPush(KEY_INPUT_SPACE))
		{
			PlaySoundMem(pushSeHandle, DX_PLAYTYPE_BACK);
			rotatePhase = RoratePhase::DECISION;
			time->Reset();
		}
		if (time->GetTimeCount() > 4000)
		{
			rotatePhase = RoratePhase::ROTATE;
			time->Reset();
			selectStage = (selectStage + 1) % stageImageHandle.size();
		}*/
		if (InputController::getInstance().GetRelease(KEY_INPUT_SPACE))
		{
			if (pressTime > 400)
			{
				PlaySoundMem(pushSeHandle, DX_PLAYTYPE_BACK);
				rotatePhase = RoratePhase::DECISION;
				time->Reset();
			}
			else
			{
				rotatePhase = RoratePhase::ROTATE;
				time->Reset();
				selectStage = (selectStage + 1) % stageImageHandle.size();
			}
		}

		if (InputController::getInstance().GetPress(KEY_INPUT_SPACE))
			pressTime += time->GetDeltaTime();
		else
			pressTime = 0;

		break;
	case StageSelect::DECISION:
		if (time->GetTimeCount() > 1000)
		{
			GameData::getInstance().Stage = selectStage;
			nextScene = std::make_shared<GameMain>();
		}
		break;
	default:
		break;
	}

#if _DEBUG
	if (InputController::getInstance().GetPush(KEY_INPUT_1))
	{
		GameData::getInstance().Stage = 0;
		nextScene = std::make_shared<GameMain>();
	}
	else if (InputController::getInstance().GetPush(KEY_INPUT_2))
	{
		GameData::getInstance().Stage = 1;
		nextScene = std::make_shared<GameMain>();
	}
	else if (InputController::getInstance().GetPush(KEY_INPUT_3))
	{
		GameData::getInstance().Stage = 2;
		nextScene = std::make_shared<GameMain>();
	}
#endif
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

	DrawExtendGraph(0, 0, x, y, backGraphHandle, TRUE);


#define SIH(num) stageImageHandle.at((selectStage + stageImageHandle.size() + num) % stageImageHandle.size()).first

	int a = static_cast<int>( 255.0 * time->GetTimeCount() / 600.0);
	switch (rotatePhase)
	{
	case StageSelect::START:
		DrawExtendGraph(Perf(x, 15.0 + 70.0 * cos(radian + 2.0 / size * PI + 0.5 * PI)), 50 + Perf(y, 10.0 - 15.0 * sin(radian + 2.0 / size * PI + 0.5 * PI)),
			Perf(x, 85.0 + 70.0 * cos(radian + 2.0 / size * PI + 0.5 * PI)), 50 + Perf(y, 80.0 - 15.0 * sin(radian + 2.0 / size * PI + 0.5 * PI)), SIH(2), FALSE);
		DrawExtendGraph(Perf(x, 15.0 + 70.0 * cos(radian - 2.0 / size * PI + 0.5 * PI)), 50 + Perf(y, 10.0 - 15.0 * sin(radian - 2.0 / size * PI + 0.5 * PI)),
			Perf(x, 85.0 + 70.0 * cos(radian - 2.0 / size * PI + 0.5 * PI)), 50 + Perf(y, 80.0 - 15.0 * sin(radian - 2.0 / size * PI + 0.5 * PI)), SIH(1), FALSE);
		DrawExtendGraph(Perf(x, 15.0 + 70.0 * cos(radian + 0.5 * PI)), 50 + Perf(y, 10.0 - 15.0 * sin(radian + 0.5 * PI)),
			Perf(x, 85.0 + 70.0 * cos(radian + 0.5 * PI)), 50 + Perf(y, 80.0 - 15.0 * sin(radian + 0.5 * PI)), SIH(0), FALSE);

		if (time->GetTimeCount() < 510)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - time->GetTimeCount() / 2);
			DrawBox(0, 0, x, y, GetColor(255, 255, 255), TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		break;
	case StageSelect::ROTATE:
		if (time->GetTimeCount() < 500)
		{
			DrawExtendGraph(Perf(x, 15.0 + 70.0 * cos(radian + 2.0 / size * PI + 0.5 * PI)), 50 + Perf(y, 10.0 - 15.0 * sin(radian + 2.0 / size * PI + 0.5 * PI)),
							Perf(x, 85.0 + 70.0 * cos(radian + 2.0 / size * PI + 0.5 * PI)), 50 + Perf(y, 80.0 - 15.0 * sin(radian + 2.0 / size * PI + 0.5 * PI)), SIH(1), FALSE);
			DrawExtendGraph(Perf(x, 15.0 + 70.0 * cos(radian - 2.0 / size * PI + 0.5 * PI)), 50 + Perf(y, 10.0 - 15.0 * sin(radian - 2.0 / size * PI + 0.5 * PI)),
							Perf(x, 85.0 + 70.0 * cos(radian - 2.0 / size * PI + 0.5 * PI)), 50 + Perf(y, 80.0 - 15.0 * sin(radian - 2.0 / size * PI + 0.5 * PI)), SIH(0), FALSE);
			DrawExtendGraph(Perf(x, 15.0 + 70.0 * cos(radian + 0.5 * PI)), 50 + Perf(y, 10.0 - 15.0 * sin(radian + 0.5 * PI)),
							Perf(x, 85.0 + 70.0 * cos(radian + 0.5 * PI)), 50 + Perf(y, 80.0 - 15.0 * sin(radian + 0.5 * PI)), SIH(2), FALSE);
		}
		else
		{
			DrawExtendGraph(Perf(x, 15.0 + 70.0 * cos(radian + 2.0 / size * PI + 0.5 * PI)), 50 + Perf(y, 10.0 - 15.0 * sin(radian + 2.0 / size * PI + 0.5 * PI)),
							Perf(x, 85.0 + 70.0 * cos(radian + 2.0 / size * PI + 0.5 * PI)), 50 + Perf(y, 80.0 - 15.0 * sin(radian + 2.0 / size * PI + 0.5 * PI)), SIH(1), FALSE);
			DrawExtendGraph(Perf(x, 15.0 + 70.0 * cos(radian + 0.5 * PI)), 50 + Perf(y, 10.0 - 15.0 * sin(radian + 0.5 * PI)),
							Perf(x, 85.0 + 70.0 * cos(radian + 0.5 * PI)), 50 + Perf(y, 80.0 - 15.0 * sin(radian + 0.5 * PI)), SIH(2), FALSE);
			DrawExtendGraph(Perf(x, 15.0 + 70.0 * cos(radian - 2.0 / size * PI + 0.5 * PI)), 50 + Perf(y, 10.0 - 15.0 * sin(radian - 2.0 / size * PI + 0.5 * PI)),
							Perf(x, 85.0 + 70.0 * cos(radian - 2.0 / size * PI + 0.5 * PI)), 50 + Perf(y, 80.0 - 15.0 * sin(radian - 2.0 / size * PI + 0.5 * PI)), SIH(0), FALSE);
		}
		break;
	case StageSelect::STOP:
		DrawExtendGraph(Perf(x, 15.0 + 70.0 * cos(radian + 2.0 / size * PI + 0.5 * PI)),	50 + Perf(y, 10.0 - 15.0 * sin(radian + 2.0 / size * PI + 0.5 * PI)),
			            Perf(x, 85.0 + 70.0 * cos(radian + 2.0 / size * PI + 0.5 * PI)),	50 + Perf(y, 80.0 - 15.0 * sin(radian + 2.0 / size * PI + 0.5 * PI)), SIH(2), FALSE);
		DrawExtendGraph(Perf(x, 15.0 + 70.0 * cos(radian - 2.0 / size * PI + 0.5 * PI)),	50 + Perf(y, 10.0 - 15.0 * sin(radian - 2.0 / size * PI + 0.5 * PI)),
						Perf(x, 85.0 + 70.0 * cos(radian - 2.0 / size * PI + 0.5 * PI)),	50 + Perf(y, 80.0 - 15.0 * sin(radian - 2.0 / size * PI + 0.5 * PI)), SIH(1), FALSE);
		DrawExtendGraph(Perf(x, 15.0 + 70.0 * cos(radian + 0.5 * PI)), 50 + Perf(y, 10.0 - 15.0 * sin(radian + 0.5 * PI)),
						Perf(x, 85.0 + 70.0 * cos(radian + 0.5 * PI)), 50 + Perf(y, 80.0 - 15.0 * sin(radian + 0.5 * PI)), SIH(0), FALSE);

		a = time->GetTimeCount();
		a = (a > 255) ? 255 : a;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
		DrawStringToHandle(350, y - 120, "’·‰Ÿ‚µ‚·‚é‚ÆŒˆ’è‚·‚é‚æI\n’Z‚­‰Ÿ‚·‚ÆŽŸ‚ð‘I‘ð‚·‚é‚æI", GetColor(255, 255, 255), fontHandle, TRUE);
		DrawExtendGraph(100, y - 500, x - 100, y - 100, stageImageHandle.at(selectStage).second, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		break;
	case StageSelect::DECISION:
		DrawExtendGraph(Perf(x, 15.0), 50 + Perf(y, 10.0 - 15.0),
			Perf(x, 85.0), 50 + Perf(y, 80.0 - 15.0), stageImageHandle.at(selectStage).first, FALSE);
		DrawExtendGraph(100, y - 450, x - 100, y - 50, stageImageHandle.at(selectStage).second, TRUE);
		if (time->GetTimeCount() < 600)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
			DrawExtendGraph(static_cast<int>(-a * 16 / 20.0) + Perf(x, 15.0), static_cast<int>(-a * 9 / 20.0) + 50 + Perf(y, 10.0 - 15.0),
				static_cast<int>(a * 16 / 20.0) + Perf(x, 85.0), static_cast<int>(a * 9 / 20.0) + 50 + Perf(y, 80.0 - 15.0), stageImageHandle.at(selectStage).first, FALSE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		
		if (time->GetTimeCount() > 40)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (550 - time->GetTimeCount()) / 2);
			DrawExtendGraph(0, 0, x, y, loadHandle, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else if (time->GetTimeCount() > 550)
		{
			DrawExtendGraph(0, 0, x, y, loadHandle, TRUE);
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