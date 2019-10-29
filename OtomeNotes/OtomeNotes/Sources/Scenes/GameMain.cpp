#include"DxLib.h"
#include<iostream>
#include <algorithm>
#include<string>

#include"GameMain.h"
#include"../MainController/InputController.h"
#include"../MainController/GameData.h"
#include"Ending.h"

GameMain::GameMain() : VirtualScene(),
	fileHandle(FileRead_open("Assets/CSV/Notes.csv")),
	fontHandle(LoadFontDataToHandle("Assets/Fonts/Senobi_m.dft",1)),
	mFontHandle(LoadFontDataToHandle("Assets/Fonts/Senobi_m64.dft", 1)),
	largeFontHandle(LoadFontDataToHandle("Assets/Fonts/Senobi_m96.dft", 1)),
	longNotesHandle(LoadGraph("Assets/Textures/GameMain/LongNotes.png")),
	textFrameHandle(LoadGraph("Assets/Textures/GameMain/TextFrame.png")),
	frameHandle(LoadGraph("Assets/Textures/GameMain/Frame.png")),
	SE_notesHandle(LoadSoundMem("Assets/Sounds/SE/note_normal.mp3")),
	bgmResultHandle(LoadSoundMem("Assets/Sounds/BGM/Result.mp3")),
	gaugeHandle(LoadGraph("Assets/Textures/GameMain/Gauge.png")),
	gaugeHandle2(LoadGraph("Assets/Textures/GameMain/Gauge2.png"))
{
	LoadDivGraph("Assets/Textures/GameMain/Button.png", 2, 1, 2, 100, 100, buttonHandle);
	notesHandle[0] = LoadGraph("Assets/Textures/GameMain/Notes.png");
	notesHandle[1] = MakeScreen(100, 100, TRUE);
	notesHandle[2] = MakeScreen(100, 100, TRUE);
	int i = GraphFilterBlt(notesHandle[0],notesHandle[1], DX_GRAPH_FILTER_HSB,0,-120,0,0);
	int j = GraphFilterBlt(notesHandle[0],notesHandle[2], DX_GRAPH_FILTER_HSB,0,60,0,0);
	LoadDivGraph("Assets/Textures/GameMain/FullTexture.png", 3, 1, 3, 640, 360, fullTextHandle);
	LoadDivGraph("Assets/Textures/GameMain/Fever2.png",2 , 1, 2, 640, 360, feverBackHandle);
	//feverBackHandle[1] = LoadGraph("Assets/Textures/GameMain/Fever2.png");
	krkrHandle = LoadGraph("Assets/Textures/Particles/Star.png");
	LoadDivGraph("Assets/Textures/Particles/Hwhw.png", 4, 1, 4, 100, 100, hwhwHandle);

	SE_resultHandle[0] = LoadSoundMem("Assets/Sounds/Voice/SystemVoice/excellent.mp3");
	SE_resultHandle[1] = LoadSoundMem("Assets/Sounds/Voice/SystemVoice/good.mp3");
	SE_resultHandle[2] = LoadSoundMem("Assets/Sounds/Voice/SystemVoice/failling.mp3");


	LoadSelectChara();

	waitTime = 0;
	popToJustTime = 1200;
	textQueueWaitTime = popToJustTime - 200;

	backGroundStep = 0;
	backGroundTime = 10000;

	int x, y, c;
	GetScreenState(&x, &y, &c);

	textX = notesX = 200;
	textY = 700;
	notesY = textY - 150;
	
	score = 0;
	scoreCount[0] = scoreCount[1] = scoreCount[2] = scoreCount[3] = 0;
	scoreColor[0] = GetColor(255, 255, 155);
	scoreColor[1] = GetColor(255, 205, 100);
	scoreColor[2] = GetColor(205, 185, 235);
	scoreColor[3] = GetColor(185, 185, 185);
	scoreName[0] = "PARFECT";
	scoreName[1] = "GOOD";
	scoreName[2] = "BAD";
	scoreName[3] = "MISS";
	feel = 50;
	fever = 0;


	phase = PhaseType::START;

	scorePopCount = 0;

	time->TimeUpdate();
	time->Reset();
}

GameMain::~GameMain()
{
	Live2D_DeleteModel(modelHandle);
	FileRead_close(fileHandle);
	DeleteFontToHandle(fontHandle);
	DeleteGraph(buttonHandle[0]);
	DeleteGraph(buttonHandle[1]);
	DeleteGraph(notesHandle[0]);
	DeleteGraph(notesHandle[1]);
	DeleteGraph(notesHandle[2]);
	DeleteGraph(backGroundHandle[0]);
	DeleteGraph(backGroundHandle[1]);
	DeleteGraph(backGroundHandle[2]);
	DeleteGraph(textFrameHandle);
}


void GameMain::Update()
{
	time->TimeUpdate();

	switch (phase)
	{
	case GameMain::PhaseType::START:
		StartUpdate();
		break;
	case GameMain::PhaseType::MAIN:
		MainUpdate();
		break;
	case GameMain::PhaseType::RESULT:
		ResultUpdate();
		break;
	case GameMain::PhaseType::NEXT:
		NextUpdate();
		break;
	}
}

void GameMain::StartUpdate()
{
	if (time->GetTimeCount() > 1000)
	{
		phase = PhaseType::MAIN;
		PlaySoundMem(bgmHandle, DX_PLAYTYPE_BACK);
		time->Reset();
	}

	// モーション再生が終了していたらアイドリングモーションをランダムで再生
	if (Live2D_Model_IsMotionFinished(modelHandle) == TRUE)
	{
		Live2D_Model_StartMotion(modelHandle, "Idle", 0);
	}

	// モデルの状態を60分の1秒分進める
	Live2D_Model_Update(modelHandle, time->GetDeltaTime() / 1000.0f);


}

void GameMain::MainUpdate()
{

	CSVRead();

	feverTime += time->GetDeltaTime();
	backGroundTime += time->GetDeltaTime();


	if (FileRead_eof(fileHandle))
	{
		time->Reset();
		phase = PhaseType::RESULT;
		StopSoundMem(bgmHandle);
		particles.clear();
	}
#if _DEBUG
	if (InputController::getInstance().GetPush(KEY_INPUT_BACK))
	{
		time->Reset();
		phase = PhaseType::RESULT;
		StopSoundMem(bgmHandle);
		particles.clear();
	}
#endif


	for (auto&& var : popText)
		var->Update(time->GetDeltaTime());

	bool active = true;
	for (auto&& var : notes)
		active = var->Update(time->GetDeltaTime(),active);

	NotesCheck();


	auto it =
		std::remove_if(notes.begin(), notes.end(), [](
			std::shared_ptr<Notes>am) {return  am->Dead; });
	notes.erase(it, notes.end());

	for (auto&& var : particles)
		var->Update(time->GetDeltaTime());

	auto itr =
		std::remove_if(particles.begin(), particles.end(), [](
			std::shared_ptr<VirtualParticle>am) {return  am->Dead; });
	particles.erase(itr, particles.end());

	for (auto&& var : backParticles)
		var->Update(time->GetDeltaTime());

	auto itrp =
		std::remove_if(backParticles.begin(), backParticles.end(), [](
			std::shared_ptr<VirtualParticle>am) {return  am->Dead; });
	backParticles.erase(itrp, backParticles.end());

	for (auto&& var : buttons)
	{
		var->Update(time->GetDeltaTime());
	}
	auto itrb =
		std::remove_if(buttons.begin(), buttons.end(), [](
			std::shared_ptr<Button>am) {return  am->Dead; });
	buttons.erase(itrb, buttons.end());

	// モーション再生が終了していたらアイドリングモーションをランダムで再生
	if (Live2D_Model_IsMotionFinished(modelHandle) == TRUE)
	{
		Live2D_Model_StartMotion(modelHandle, "Idle", 0);
	}

	// モデルの状態を60分の1秒分進める
	Live2D_Model_Update(modelHandle, time->GetDeltaTime() / 1000.0f);

	if (InputController::getInstance().GetPush(KEY_INPUT_SPACE))
	{
		PlaySoundMem(SE_notesHandle, DX_PLAYTYPE_BACK);
	}
}

void GameMain::ResultUpdate()
{
	if (time->GetTimeCount() > 3000 && scorePopCount == 0)
	{
		PlaySoundMem(bgmResultHandle, DX_PLAYTYPE_LOOP);
		scorePopCount++;
		if (fever == 1)
		{
			backParticles.push_back(std::make_shared<Hwhw>(640, 150, hwhwHandle[0], 0, 3.0));
			Live2D_Model_StartMotion(modelHandle, "Parfect", 0);
			PlaySoundMem(resultVoiceHandle[0], DX_PLAYTYPE_BACK);
		}
		else if (fever == 0)
		{
			backParticles.push_back(std::make_shared<Hwhw>(640, 150, hwhwHandle[1], 0, 3.0));
			Live2D_Model_StartMotion(modelHandle, "Good", 0);
			PlaySoundMem(resultVoiceHandle[1], DX_PLAYTYPE_BACK);
		}
		else if (fever == -1)
		{
			backParticles.push_back(std::make_shared<Doyon>(540, 100, hwhwHandle[2], 130));
			backParticles.push_back(std::make_shared<Doyon>(760, 150, hwhwHandle[3], 100));
			Live2D_Model_StartMotion(modelHandle, "Bad", 0);
			PlaySoundMem(resultVoiceHandle[2], DX_PLAYTYPE_BACK);
		}
	}
	/*else if (time->GetTimeCount() > 6000 && scorePopCount == 1)
	{
		scorePopCount++;
		particles.push_back(std::make_shared<Krkr>(890, 480, krkrHandle, 0,4.0));
	}*/
	else if ((time->GetTimeCount() > 10000 && InputController::getInstance().GetPush(KEY_INPUT_SPACE)) ||
		time->GetTimeCount() > 20000)
	{
		phase = PhaseType::NEXT;
		time->Reset();
	}


	for (auto&& var : particles)
		var->Update(time->GetDeltaTime());

	auto itr =
		std::remove_if(particles.begin(), particles.end(), [](
			std::shared_ptr<VirtualParticle>am) {return  am->Dead; });
	particles.erase(itr, particles.end());

	for (auto&& var : backParticles)
		var->Update(time->GetDeltaTime());

	auto itrp =
		std::remove_if(backParticles.begin(), backParticles.end(), [](
			std::shared_ptr<VirtualParticle>am) {return  am->Dead; });
	backParticles.erase(itrp, backParticles.end());

	// モーション再生が終了していたらアイドリングモーションをランダムで再生
	if (Live2D_Model_IsMotionFinished(modelHandle) == TRUE)
	{
		Live2D_Model_StartMotion(modelHandle, "Idle", 0);
	}

	// モデルの状態を60分の1秒分進める
	Live2D_Model_Update(modelHandle, time->GetDeltaTime() / 1000.0f);

}

void GameMain::NextUpdate()
{
	if (time->GetTimeCount() > 510)
	{
		GameData::getInstance().BgmHandle = bgmResultHandle;
		nextScene = std::make_shared<Ending>();
	}
}

void GameMain::Draw() const
{
	switch (phase)
	{
	case GameMain::PhaseType::START:
		StartDraw();
		break;
	case GameMain::PhaseType::MAIN:
		MainDraw();
		break;
	case GameMain::PhaseType::RESULT:
		ResultDraw();
		break;
	case GameMain::PhaseType::NEXT:
		NextDraw();
		break;
	}
}

void GameMain::StartDraw() const
{
	int x, y, c;
	GetScreenState(&x, &y, &c);

	DrawExtendGraph(0, 0, x, y, backGroundHandle[backGroundStep], FALSE);

	if(time->GetTimeCount() < 300)
		DrawExtendGraph(0, 0, x, y, fullTextHandle[0], FALSE);
	else if (time->GetTimeCount() < 1020)
	{
		// Live2D描画の開始
		Live2D_RenderBegin();

		// モデルの描画
		Live2D_Model_Draw(modelHandle);

		// Live2D描画の終了
		Live2D_RenderEnd();

		DrawExtendGraph(50, y - 300, x - 50, y, textFrameHandle, TRUE);
		DrawStringToHandle(100, y - 280, charaName.c_str(), GetColor(255,255,255), fontHandle);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (time->GetTimeCount() - 300) / 3);
		DrawExtendGraph(0, 0, x, y, fullTextHandle[0], FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

}

void GameMain::MainDraw() const
{
	int x, y, c;
	GetScreenState(&x, &y, &c);

	if (backGroundTime < 1280)
	{
		DrawExtendGraph(backGroundTime, 0, x + backGroundTime, y, backGroundHandle[backGroundStep - 1], FALSE);
		DrawExtendGraph(backGroundTime - 1280, 0, x + backGroundTime - 1280, y, backGroundHandle[backGroundStep], FALSE);
	}
	else
		DrawExtendGraph(0, 0, x, y, backGroundHandle[backGroundStep], FALSE);
	FeverDraw(x,y);

	for (auto&& var : backParticles)
		var->Draw();

	// Live2D描画の開始
	Live2D_RenderBegin();

	// モデルの描画
	Live2D_Model_Draw(modelHandle);

	// Live2D描画の終了
	Live2D_RenderEnd();

	DrawExtendGraph(50, y - 300, x - 50, y, textFrameHandle, TRUE);
	DrawStringToHandle(100, y - 280, charaName.c_str(), GetColor(255, 255, 255), fontHandle);

	GaugeDraw(x, y);


	for (auto&& var : popText)
		var->Draw(fontHandle);

	for (auto&& var : notes)
		var->Draw();

	for (auto&& var : buttons)
		var->Draw();

	for (auto&& var : particles)
		var->Draw();

}

void GameMain::ResultDraw() const
{
	int x, y, c;
	GetScreenState(&x, &y, &c);

	DrawExtendGraph(0, 0, x, y, backGroundHandle[backGroundStep], FALSE);

	FeverDraw(x, y);

	for (auto&& var : backParticles)
		var->Draw();




	// Live2D描画の開始
	Live2D_RenderBegin();

	// モデルの描画
	Live2D_Model_Draw(modelHandle);

	// Live2D描画の終了
	Live2D_RenderEnd();

	GaugeDraw(x, y);


	if (time->GetTimeCount() < 1000)
	{
		DrawExtendGraph(50, y - 300 + time->GetTimeCount() / 2, x - 50, y + time->GetTimeCount() / 2, textFrameHandle, TRUE);
	}



	ScoreDraw(x,y);

	for (auto&& var : particles)
		var->Draw();

}

void GameMain::NextDraw() const
{
	int x, y, c;
	GetScreenState(&x, &y, &c);

	DrawExtendGraph(0, 0, x, y, backGroundHandle[backGroundStep], FALSE);

	FeverDraw(x, y);

	// Live2D描画の開始
	Live2D_RenderBegin();

	// モデルの描画
	Live2D_Model_Draw(modelHandle);

	// Live2D描画の終了
	Live2D_RenderEnd();

	
	for (int i = 0; i < 4; i++)
	{
		DrawExtendGraph(50, y - 320 + i * 60, 350, y - 260 + i * 60, frameHandle, TRUE);
		DrawStringToHandle(60, y - 310 + i * 60, scoreName[i].c_str(), scoreColor[i], fontHandle);
		DrawStringToHandle(240, y - 310 + i * 60,
			ScoreCountTostring(i, 1, 1).c_str(), scoreColor[i], fontHandle);
	}
	DrawExtendGraph(50, y - 420, 350, y - 340, frameHandle, TRUE);
	DrawStringToHandle(60, y - 400, "SCORE", GetColor(255, 255, 255), fontHandle);
	DrawStringToHandle(240, y - 400,
		ScoreCountTostring(5, 1, 1).c_str(), GetColor(255, 255, 255), fontHandle);

	if (time->GetTimeCount() < 510)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, time->GetTimeCount() / 2);
		DrawBox(0, 0, x, y, GetColor(255, 255, 255), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else
		DrawBox(0, 0, x, y, GetColor(255, 255, 255), TRUE);

	//評価
	DrawExtendGraph(720, 440, 1170, 540, frameHandle, TRUE);
	if (fever == 1)
		DrawStringToHandle(740, 460, "EXCELLENT", scoreColor[0], mFontHandle);
	else if (fever == 0)
		DrawStringToHandle(740, 460, "  GOOD", scoreColor[1], mFontHandle);
	else if (fever == -1)
		DrawStringToHandle(740, 460, " FAILED", scoreColor[2], mFontHandle);

}

void GameMain::GaugeDraw(int x,int y) const
{
	int destHandle;
	destHandle = MakeScreen(50, 720, TRUE);

	switch (fever)
	{
	case 0:
		DrawExtendGraph(x - 120, 50, x - 50, y - 300, gaugeHandle, TRUE);
		break;
	case 1:
		GraphFilterBlt(gaugeHandle, destHandle, DX_GRAPH_FILTER_HSB, 0, 70, 120, 30);
		DrawExtendGraph(x -  120, 50, x  - 50, y - 300, destHandle, TRUE);
		break;
	case -1:
		GraphFilterBlt(gaugeHandle, destHandle, DX_GRAPH_FILTER_HSB, 0, -60, 100, 0);
		DrawExtendGraph(x - 120, 50, x - 50, y - 300, destHandle, TRUE);
		break;
	}
	DrawExtendGraph(x -  135, (y - 350) * (100 - feel) / 100 + 10, x - 35, (y - 350) * (100 - feel) / 100 + 90, gaugeHandle2, TRUE);
}

void GameMain::FeverDraw(int x, int y) const
{
	if (fever == 0)
		return;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 165 + static_cast<int>(cos(feverTime / 370.0) * 80));
	int yy = static_cast<int>( sin(feverTime / 500.0) * 10.0);
	DrawExtendGraph(0, -10 + yy, x, y + 10 + yy, feverBackHandle[1 - (fever == -1)], TRUE);
	
	//SetDrawBlendMode(DX_BLENDMODE_ADD, 125 + static_cast<int>(cos(feverTime / 370.0) * 120 + 3.0));
	//DrawExtendGraph(0, -10 - yy, x, y + 10 - yy, feverBackHandle[1 - (fever == -1)], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameMain::ScoreDraw(int x, int y) const
{
	if (time->GetTimeCount() < 6000)
		return;

	if (time->GetTimeCount() < 6510)
	{
		int temp = (6510 - time->GetTimeCount()) / 2;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - temp);
		for (int i = 0; i < 4; i++)
		{
			DrawExtendGraph(50, y - 320 + i * 60 + temp, 350, y - 260 + i * 60 + temp, frameHandle, TRUE);
			DrawStringToHandle(60, y - 310 + i * 60 + temp, scoreName[i].c_str(), scoreColor[i], fontHandle);
			DrawStringToHandle(240, y - 310 + i * 60 + temp,
				ScoreCountTostring(i, 0,1).c_str(), scoreColor[i], fontHandle);
		}

		DrawExtendGraph(50, y - 420 + temp, 350, y - 340 + temp, frameHandle, TRUE);
		DrawStringToHandle(60, y - 400 + temp, "SCORE", GetColor(255,255,255), fontHandle);
		DrawStringToHandle(240, y - 400 + temp,
			ScoreCountTostring(5, 0, 1).c_str(), GetColor(255, 255, 255), fontHandle);

		//評価
		DrawExtendGraph(720, 440 + temp, 1170, 540 + temp, frameHandle, TRUE);
		if (fever == 1)
			DrawStringToHandle(740, 460 + temp, "EXCELLENT", scoreColor[0], mFontHandle);
		else if (fever == 0)
			DrawStringToHandle(740, 460 + temp, "  GOOD", scoreColor[1], mFontHandle);
		else if (fever == -1)
			DrawStringToHandle(740, 460 + temp, " FAILED", scoreColor[2], mFontHandle);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	}
	else if(time->GetTimeCount() < 7010)
	{
		for (int i = 0; i < 4; i++)
		{
			DrawExtendGraph(50, y - 320 + i * 60, 350, y - 260 + i * 60, frameHandle, TRUE);
			DrawStringToHandle(60, y - 310 + i * 60, scoreName[i].c_str(), scoreColor[i], fontHandle);
			DrawStringToHandle(240, y - 310 + i * 60, 
				ScoreCountTostring(i,time->GetTimeCount() - 6510,500).c_str(), scoreColor[i], fontHandle);
		}	
		DrawExtendGraph(50, y - 420, 350, y - 340, frameHandle, TRUE);
		DrawStringToHandle(60, y - 400, "SCORE", GetColor(255, 255, 255), fontHandle);
		DrawStringToHandle(240, y - 400,
			ScoreCountTostring(5, time->GetTimeCount() - 6510,500).c_str(), GetColor(255, 255, 255), fontHandle);

		//評価
		DrawExtendGraph(720, 440, 1170, 540, frameHandle, TRUE);
		if (fever == 1)
			DrawStringToHandle(740, 460, "EXCELLENT", scoreColor[0], mFontHandle);
		else if (fever == 0)
			DrawStringToHandle(740, 460, "  GOOD", scoreColor[1], mFontHandle);
		else if (fever == -1)
			DrawStringToHandle(740, 460, " FAILED", scoreColor[2], mFontHandle);

	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			DrawExtendGraph(50, y - 320 + i * 60, 350, y - 260 + i * 60, frameHandle, TRUE);
			DrawStringToHandle(60, y - 310 + i * 60, scoreName[i].c_str(), scoreColor[i], fontHandle);
			DrawStringToHandle(240, y - 310 + i * 60,
				ScoreCountTostring(i, 1,1).c_str(), scoreColor[i], fontHandle);
		}
		DrawExtendGraph(50, y - 420, 350, y - 340, frameHandle, TRUE);
		DrawStringToHandle(60, y - 400, "SCORE", GetColor(255, 255, 255), fontHandle);
		DrawStringToHandle(240, y - 400,
			ScoreCountTostring(5, 1, 1).c_str(), GetColor(255, 255, 255), fontHandle);

		//評価
		DrawExtendGraph(720, 440, 1170, 540, frameHandle, TRUE);
		if (fever == 1)
			DrawStringToHandle(740, 460, "EXCELLENT", scoreColor[0], mFontHandle);
		else if (fever == 0)
			DrawStringToHandle(740, 460, "  GOOD", scoreColor[1], mFontHandle);
		else if (fever == -1)
			DrawStringToHandle(740, 460, " FAILED", scoreColor[2], mFontHandle);

	}

}

void GameMain::LoadSelectChara()
{
	//Himeka
	if (GameData::getInstance().Stage == 0)
	{
		modelHandle = Live2D_LoadModel("Assets/Live2d/Himeka/Himeka.model3.json");
		LoadDivGraph("Assets/Textures/GameMain/HimekaBackGround.png", 3, 1, 3, 640, 360, backGroundHandle);

		Live2D_Model_SetExtendRate(modelHandle, 1.5f,1.5f);
		Live2D_Model_SetTranslate(modelHandle, 0.0f, -110.0f);

		bgmHandle = LoadSoundMem("Assets/Sounds/BGM/Himeka.mp3");

		resultVoiceHandle[0] = LoadSoundMem("Assets/Sounds/Voice/Himeka/r1_01.wav");
		resultVoiceHandle[1] = LoadSoundMem("Assets/Sounds/Voice/Himeka/r2_01.wav");
		resultVoiceHandle[2] = LoadSoundMem("Assets/Sounds/Voice/Himeka/r3_01.wav");

		charaName = "刑部 姫花";
	}
	//Himari
	else if (GameData::getInstance().Stage == 1)
	{
		modelHandle = Live2D_LoadModel("Assets/Live2d/Mahiru/mahiru.model3.json");
		LoadDivGraph("Assets/Textures/GameMain/HimekaBackGround.png", 3, 1, 3, 640, 360, backGroundHandle);

		Live2D_Model_SetExtendRate(modelHandle, 1.5f, 1.5f);
		Live2D_Model_SetTranslate(modelHandle, 0.0f, -110.0f);

		bgmHandle = LoadSoundMem("Assets/Sounds/BGM/Himeka.mp3");

		resultVoiceHandle[0] = LoadSoundMem("Assets/Sounds/Voice/Mahiru/r1.mp3");
		resultVoiceHandle[1] = LoadSoundMem("Assets/Sounds/Voice/Mahiru/r2.mp3");
		resultVoiceHandle[2] = LoadSoundMem("Assets/Sounds/Voice/Mahiru/r3.mp3");

		charaName = "まひる";
	}
	//Manami
	else if(GameData::getInstance().Stage == 2)
	{
		modelHandle = Live2D_LoadModel("Assets/Live2d/Manami/manami.model3.json");
		LoadDivGraph("Assets/Textures/GameMain/HimekaBackGround.png", 3, 1, 3, 640, 360, backGroundHandle);

		Live2D_Model_SetExtendRate(modelHandle, 1.5f, 1.5f);
		Live2D_Model_SetTranslate(modelHandle, 0.0f, -90.0f);

		bgmHandle = LoadSoundMem("Assets/Sounds/BGM/Satsuki.mp3");

		resultVoiceHandle[0] = LoadSoundMem("Assets/Sounds/Voice/Manami/r1.mp3");
		resultVoiceHandle[1] = LoadSoundMem("Assets/Sounds/Voice/Manami/r2.mp3");
		resultVoiceHandle[2] = LoadSoundMem("Assets/Sounds/Voice/Manami/r3.mp3");

		charaName = "エロ師匠";
	}
}

void GameMain::CSVRead()
{
	if (waitTime <= 0 && !FileRead_eof(fileHandle))
	{
		FileRead_gets(readText, 256, fileHandle);

		waitTextQueue.push(CharClass(readText));

		int addTime = (readText[3] - '0') * 1000
			+ (readText[4] - '0') * 100
			+ (readText[5] - '0') * 10
			+ (readText[6] - '0') * 1;

		if (readText[8] == 'C' || readText[8] == 'E')
		{
			notesX = 200;
			for (auto&& var : buttons)
				var->End();
			buttons.push_back(std::make_shared<Button>(buttonHandle, popToJustTime));
		}
		if (readText[0] == 'N')
		{
			NotesPush(readText[1]);
		}
		notesX += addTime / 5;

		waitTime += addTime;
	}

	waitTime -= time->GetDeltaTime();

	if (textQueueWaitTime <= 0)
	{
		QueueRead();
	}

	textQueueWaitTime -= time->GetDeltaTime();
}

void GameMain::NotesPush(char _notesType)
{
	if (readText[1] == 'N')
		notes.push_back(std::make_shared<Notes>(notesHandle[0],buttonHandle[1], notesX, notesY));
	else if (readText[1] == 'L')
		notes.push_back(std::make_shared<LongNotes>(notesHandle[1], buttonHandle[1],notesX,notesY,
		(readText[10] - '0') * 1000 + (readText[11] - '0') * 100 + (readText[12] - '0') * 10 + (readText[13] - '0'),
			longNotesHandle));
	else if (readText[1] == 'R')
		notes.push_back(std::make_shared<RepeatedNotes>(notesHandle[2], buttonHandle[1], notesX, notesY,
		(readText[10] - '0') * 1000 + (readText[11] - '0') * 100 + (readText[12] - '0') * 10 + (readText[13] - '0'),
			longNotesHandle));
}

void GameMain::NotesCheck()
{
	for (auto&& var : notes)
	{
		int eva = var->Evalution;

		if (eva == Notes::EvalutionType::DEFAULT)
			return;

		scoreCount[eva]++;
		PlaySoundMem(SE_notesHandle, DX_PLAYTYPE_BACK);

		auto i = buttons.at(0)->GetTime() / 5 - 40;
		switch (eva)
		{
		case Notes::EvalutionType::PERFECT:
			score += 20;
			AddFeel(5);
			particles.push_back(std::make_shared<Krkr>(i, notesY, krkrHandle, 0, 2.0));
			backParticles.push_back(std::make_shared<Hwhw>(640, 150, hwhwHandle[0], 0, 3.0));
			Live2D_Model_StartMotion(modelHandle, "Parfect", 0);
			break;
		case Notes::EvalutionType::GOOD:
			score += 15;
			AddFeel(2);
			particles.push_back(std::make_shared<Krkr>(i, notesY, krkrHandle, 0, 2.0));
			backParticles.push_back(std::make_shared<Hwhw>(640, 150, hwhwHandle[1], 0, 3.0));
			Live2D_Model_StartMotion(modelHandle, "Good", 0);
			break;
		case Notes::EvalutionType::BAD:
			score += 5;
			AddFeel(-6);
			backParticles.push_back(std::make_shared<Doyon>(540, 100, hwhwHandle[2], 130));
			backParticles.push_back(std::make_shared<Doyon>(760, 150, hwhwHandle[3], 100));
			Live2D_Model_StartMotion(modelHandle, "Bad", 0);
			break;
		case Notes::EvalutionType::MISS:
			AddFeel(-10);
			backParticles.push_back(std::make_shared<Doyon>(540, 100, hwhwHandle[2], 130));
			backParticles.push_back(std::make_shared<Doyon>(760, 150, hwhwHandle[3], 100));
			Live2D_Model_StartMotion(modelHandle, "Bad", 0);
			break;
		}

		particles.push_back(std::make_shared<EvalutionText>(i, 600, fontHandle, scoreName[eva].c_str(), scoreColor[eva]));
		particles.push_back(std::make_shared<NotesButton>(i, notesY, buttonHandle[0]));

		var->Push();		
	}
}

void GameMain::QueueRead()
{
	if (waitTextQueue.empty())
		return;

	auto text = waitTextQueue.front().Text;

	waitTextQueue.pop();

	if (text[8] == 'C')
	{
		popText.clear();
		textX = 200;
		textY = 600;
	}
	else if (text[8] == 'E')
	{
		textX = 200;
		textY += 50;
	}
	else if (text[8] == 'B')
	{
		backGroundStep++;
		backGroundTime = 0;
	}

	int addTime = (text[3] - '0') * 1000
		+ (text[4] - '0') * 100
		+ (text[5] - '0') * 10
		+ (text[6] - '0') * 1;

	if (text[0] != 'N')
	{
		popText.push_back(std::make_unique<PopText>(text, textX, textY, GetColor(255, 255, 255)));
	}
	textX += addTime / 5;

	textQueueWaitTime += addTime;
}

void GameMain::AddFeel(int addFeel)
{
	feel += addFeel;
	feel = (feel > 100) ? 100 : feel;
	feel = (feel < 0) ? 0 : feel;

	int f = (feel >= 80) - (feel <= 20);
	feverTime = (f != fever) ? 0 : feverTime;
	fever = f;
}

std::string GameMain::ScoreCountTostring(int num, int numerator, int denominator) const
{
	int count;
	if (num == 5)
		count = score * numerator / denominator;
	else
		count = scoreCount[num] * numerator / denominator;
	auto c0 = 3;
	c0 -= (count == 0) ? 0 : static_cast<int>(std::log10(count));
	std::string s;
	for (int i = 0; i < c0; i++)
	{
		s += '0';
	}
	s += std::to_string(count);

	return s;
}

template <typename T> void GameMain::UpdateAndDelete(std::vector<T>&& t, int deltaTime)
{
	for (auto var : t)
	{
		var->Update(deltaTime);
	}

	auto it =
		std::remove_if(t.begin(), t.end(), [](
			T am) {return  am->Dead; });

	t.erase(it, t.end());
}

GameMain::CharClass::CharClass(char* _text)
{
	memcpy(Text, _text, sizeof(Text));
}