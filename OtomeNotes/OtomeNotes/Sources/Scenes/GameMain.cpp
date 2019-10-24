#include"DxLib.h"
#include<iostream>
#include <algorithm>

#include"GameMain.h"
#include"../MainController/InputController.h"

GameMain::GameMain() : VirtualScene(),
	modelHandle(Live2D_LoadModel("Assets/Live2d/Hiyori/Hiyori.model3.json")),
	fileHandle(FileRead_open("Assets/CSV/Notes.csv")),
	fontHandle(LoadFontDataToHandle("Assets/Fonts/Senobi_m.dft",1)),
	buttonHandle(LoadGraph("Assets/Textures/GameMain/Button.png")),
	//notesHandle(LoadGraph("Assets/Textures/GameMain/Notes.png")),
	osakabechankariHandle(LoadGraph("Assets/Textures/GameMain/Osakabechankari.png")),
	roomHandle(LoadGraph("Assets/Textures/GameMain/room.jpg")),
	textFrameHandle(LoadGraph("Assets/Textures/GameMain/TextFrame.png")),
	SE_notesHandle(LoadSoundMem("Assets/Sounds/SE/Notes.mp3"))
{
	notesHandle[0] = LoadGraph("Assets/Textures/GameMain/Notes.png");
	notesHandle[1] = MakeScreen(200, 200, TRUE);
	notesHandle[2] = MakeScreen(200, 200, TRUE);
	int i = GraphFilterBlt(notesHandle[0],notesHandle[1], DX_GRAPH_FILTER_HSB,0,90,0,0);
	int j = GraphFilterBlt(notesHandle[0],notesHandle[2], DX_GRAPH_FILTER_HSB,0,60,0,0);
	LoadDivGraph("Assets/Textures/GameMain/LongNotes.png",3,1,3,200,100,LongNotesHandle);
	bgmHandle = LoadSoundMem("Assets/Sounds/BGM/Himeka.wav");
	LoadDivGraph("Assets/Textures/GameMain/FullTexture.png", 3, 1, 3, 640, 360, fullTextHandle);
	krkrHandle = LoadGraph("Assets/Textures/Particles/Star.png");

	waitTime = 0;
	popToJustTime = 1200;
	textQueueWaitTime = popToJustTime - 200;

	int x, y, c;
	GetScreenState(&x, &y, &c);

	textX = 200;
	textY = 600;

	notesX = x - 250;
	notesY = y - 120;
	
	score = 0;
	scoreCount[0] = scoreCount[1] = scoreCount[2] = 0;

	printfDx("%d\n",modelHandle);
	Live2D_Model_SetExtendRate(modelHandle, 0.6f,0.6f);

	phase = PhaseType::START;

	scorePopCount = 0;

	time->TimeUpdate();
}

GameMain::~GameMain()
{
	Live2D_DeleteModel(modelHandle);
	FileRead_close(fileHandle);
	DeleteFontToHandle(fontHandle);
	DeleteGraph(buttonHandle);
	DeleteGraph(notesHandle[0]);
	DeleteGraph(notesHandle[1]);
	DeleteGraph(notesHandle[2]);
	DeleteGraph(osakabechankariHandle);
	DeleteGraph(roomHandle);
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
	}
}

void GameMain::StartUpdate()
{
	if (InputController::getInstance().GetPush(KEY_INPUT_Z))
	{
		phase = PhaseType::MAIN;
		//PlaySoundMem(bgmHandle, DX_PLAYTYPE_BACK);
		time->Reset();
	}
}

void GameMain::MainUpdate()
{

	CSVRead();

	if (FileRead_eof(fileHandle) || InputController::getInstance().GetPush(KEY_INPUT_BACK))
	{
		time->Reset();
		phase = PhaseType::RESULT;
	}

	for (auto&& var : popText)
		var->Update(time->GetDeltaTime());

	for (auto&& var : notes)
		var->Update(time->GetDeltaTime());

	for (auto&& var : notes)
	{
		if (var->Evalution != Notes::EvalutionType::DEFAULT)
		{
			scoreCount[var->Evalution]++;
			PlaySoundMem(SE_notesHandle, DX_PLAYTYPE_BACK);
			switch (var->Evalution)
			{
			case Notes::EvalutionType::GOOD:
				score += 100;
				particles.push_back(std::make_shared<EvalutionText>(800, 680, fontHandle, "GOOD", GetColor(255, 205, 100)));
				particles.push_back(std::make_shared<NotesButton>(notesX, notesY, buttonHandle));
				particles.push_back(std::make_shared<Krkr>(notesX, notesY, krkrHandle, 0));
				break;
			case Notes::EvalutionType::PERFECT:
				score += 200;
				particles.push_back(std::make_shared<EvalutionText>(800, 680, fontHandle, "PERFECT", GetColor(255, 255, 155)));
				particles.push_back(std::make_shared<NotesButton>(notesX, notesY, buttonHandle));
				particles.push_back(std::make_shared<Krkr>(notesX, notesY, krkrHandle, 0));
				break;
			case Notes::EvalutionType::BAD:
				score -= 100;
				particles.push_back(std::make_shared<EvalutionText>(800, 680, fontHandle, "BAD", GetColor(205, 185, 235)));
				particles.push_back(std::make_shared<NotesButton>(notesX, notesY, buttonHandle));
				break;
			}
			var->Push();
		}
	}

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

	// モーション再生が終了していたらアイドリングモーションをランダムで再生
	if (Live2D_Model_IsMotionFinished(modelHandle) == TRUE)
	{
		Live2D_Model_StartMotion(modelHandle, "Idle", GetRand(8));
	}

	// モデルの状態を60分の1秒分進める
	Live2D_Model_Update(modelHandle, time->GetDeltaTime() / 1000.0f);

}

void GameMain::ResultUpdate()
{
	if (time->GetTimeCount() > 1000 + scorePopCount * 600 && scorePopCount < 3)
	{
		particles.push_back(std::make_shared<Krkr>(200, 150 + scorePopCount * 60, krkrHandle, 120));
		scorePopCount++;
	}

	for (auto&& var : particles)
		var->Update(time->GetDeltaTime());

	auto itr =
		std::remove_if(particles.begin(), particles.end(), [](
			std::shared_ptr<VirtualParticle>am) {return  am->Dead; });
	particles.erase(itr, particles.end());

	// モーション再生が終了していたらアイドリングモーションをランダムで再生
	if (Live2D_Model_IsMotionFinished(modelHandle) == TRUE)
	{
		Live2D_Model_StartMotion(modelHandle, "Idle", GetRand(8));
	}

	// モデルの状態を60分の1秒分進める
	Live2D_Model_Update(modelHandle, time->GetDeltaTime() / 1000.0f);

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
	}
}

void GameMain::StartDraw() const
{
	int x, y, c;
	GetScreenState(&x, &y, &c);

	DrawExtendGraph(0, 0, x, y, fullTextHandle[1], FALSE);

	if (time->GetTimeCount() < 1020)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - time->GetTimeCount() / 4);
		DrawExtendGraph(0, 0, x, y, fullTextHandle[0], FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void GameMain::MainDraw() const
{
	int x, y, c;
	GetScreenState(&x, &y, &c);

	DrawExtendGraph(0, 0, x, y, roomHandle, FALSE);
	DrawExtendGraph(x / 2 - 153, 100, x / 2 + 153, 100 + 616, osakabechankariHandle, TRUE);
	DrawExtendGraph(50, y - 300, x - 50, y, textFrameHandle, TRUE);

	for (auto&& var : popText)
		var->Draw(fontHandle);

	DrawExtendGraph(notesX - 70, notesY - 70, notesX + 70, notesY + 70, buttonHandle, TRUE);
	for (auto&& var : notes)
		var->Draw(notesX, notesY);

	for (auto&& var : particles)
		var->Draw();

	// Live2D描画の開始
	Live2D_RenderBegin();

	// モデルの描画
	Live2D_Model_Draw(modelHandle);

	// Live2D描画の終了
	Live2D_RenderEnd();

}

void GameMain::ResultDraw() const
{
	int x, y, c;
	GetScreenState(&x, &y, &c);

	if (time->GetTimeCount() < x / 2)
	{
		DrawExtendGraph(0, 0, x, y, roomHandle, FALSE);
		DrawExtendGraph(-x + time->GetTimeCount() * 2, 0, time->GetTimeCount() * 2, y, fullTextHandle[2], FALSE);
	}
	else
		DrawExtendGraph(0,0, x, y, fullTextHandle[2], FALSE);

	DrawExtendGraph(x / 2 - 153, 100, x / 2 + 153, 100 + 616, osakabechankariHandle, TRUE);
	if (time->GetTimeCount() < x / 2)
	{
		DrawExtendGraph(50 + time->GetTimeCount() * 2, y - 300, x - 50 + time->GetTimeCount() * 2, y, textFrameHandle, TRUE);
	}

	if(time->GetTimeCount() > 1200)
		DrawStringToHandle(150, 150, "PERFECT", GetColor(255, 205, 100), fontHandle);

	if (time->GetTimeCount() > 1800)
		DrawStringToHandle(150, 210, "GOOD", GetColor(255, 255, 155), fontHandle);

	if (time->GetTimeCount() > 2400)
		DrawStringToHandle(150, 270, "BAD", GetColor(205, 185, 235), fontHandle);


	for (auto&& var : particles)
		var->Draw();

	// Live2D描画の開始
	Live2D_RenderBegin();

	// モデルの描画
	Live2D_Model_Draw(modelHandle);

	// Live2D描画の終了
	Live2D_RenderEnd();

}

void GameMain::CSVRead()
{
	if (waitTime <= 0 && !FileRead_eof(fileHandle))
	{
		FileRead_gets(readText, 256, fileHandle);

		waitTextQueue.push(CharClass(readText));

		if (readText[0] == 'N')
		{
			NotesPush(readText[1]);
		}

		waitTime += (readText[3] - '0') * 1000;
		waitTime += (readText[4] - '0') * 100;
		waitTime += (readText[5] - '0') * 10;
		waitTime += readText[6] - '0';
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
		notes.push_back(std::make_shared<Notes>(notesHandle[0]));
	else if (readText[1] == 'L')
		notes.push_back(std::make_shared<LongNotes>(notesHandle[1],
		(readText[10] - '0') * 1000 + (readText[11] - '0') * 100 + (readText[12] - '0') * 10 + (readText[13] - '0'),
			LongNotesHandle));
	else if (readText[1] == 'R')
		notes.push_back(std::make_shared<RepeatedNotes>(notesHandle[2],
		(readText[10] - '0') * 1000 + (readText[11] - '0') * 100 + (readText[12] - '0') * 10 + (readText[13] - '0'),
			LongNotesHandle));
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

	if (text[0] != 'N')
	{
		popText.push_back(std::make_unique<PopText>(text, textX, textY, GetColor(255, 255, 255)));
		textX += 30;
	}

	textQueueWaitTime += (text[3] - '0') * 1000;
	textQueueWaitTime += (text[4] - '0') * 100;
	textQueueWaitTime += (text[5] - '0') * 10;
	textQueueWaitTime += text[6] - '0';
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