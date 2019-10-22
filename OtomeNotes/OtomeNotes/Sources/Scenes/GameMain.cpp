#include"DxLib.h"
#include<iostream>
#include <algorithm>

#include"GameMain.h"
#include"../Particles/EvalutionText.h"


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

	waitTime = 0;

	textX = 200;
	textY = 600;

	score = 0;

	printfDx("%d",modelHandle);
	Live2D_Model_SetExtendRate(modelHandle, 0.6f,0.6f);
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

	TextRead();

	for (auto&& var : popText)
	{
		var->Update(time->GetDeltaTime());
	}

	for (auto&& var : notes)
	{
		var->Update(time->GetDeltaTime());
	}

	for (auto&& var : notes)
	{
		if (var->Evalution != Notes::EvalutionType::DEFAULT)
		{
			PlaySoundMem(SE_notesHandle, DX_PLAYTYPE_BACK);
			switch (var->Evalution)
			{
			case Notes::EvalutionType::GOOD:
				score += 1000;
				particles.push_back(std::make_shared<EvalutionText>(800, 680, fontHandle, "GOOD", GetColor(255, 205, 100)));
				break;
			case Notes::EvalutionType::PERFECT:
				score += 2000;
				particles.push_back(std::make_shared<EvalutionText>(800, 680, fontHandle, "PERFECT", GetColor(255, 255, 155)));
				break;
			case Notes::EvalutionType::BAD:
				score += 50;
				particles.push_back(std::make_shared<EvalutionText>(800, 680, fontHandle, "BAD", GetColor(205, 185, 235)));
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
	{
		var->Update(time->GetDeltaTime());
	}
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
	int x, y, c;
	GetScreenState(&x, &y, &c);


	DrawExtendGraph(0, 0, x, y, roomHandle, FALSE);
	DrawExtendGraph(x / 2 - 153, 100, x / 2 + 153, 100 + 616, osakabechankariHandle, TRUE);
	DrawExtendGraph(50, y - 300, x - 50, y, textFrameHandle, TRUE);


	for (auto&& var : popText)
	{
		var->Draw(fontHandle);
	}

	int centerX = x - 300;
	int centerY = y - 120;
	DrawExtendGraph(centerX - 70, centerY - 70, centerX + 70, centerY + 70, buttonHandle, TRUE);
	for (auto&& var : notes)
	{
		var->Draw(centerX,centerY);
	}

	for (auto&& var : particles)
	{
		var->Draw();
	}

	// Live2D描画の開始
	Live2D_RenderBegin();

	// モデルの描画
	Live2D_Model_Draw(modelHandle);

	// Live2D描画の終了
	Live2D_RenderEnd();
}

void GameMain::TextRead()
{
	if (waitTime <= 0 && !FileRead_eof(fileHandle))
	{
		FileRead_gets(readText, 256, fileHandle);

		if (readText[8] == 'C')
		{
			popText.clear();
			textX = 200;
			textY = 600;
		}
		else if (readText[8] == 'E')
		{
			textX = 200;
			textY += 50;
		}

		printfDx("%s\n",readText);
		if (readText[0] == 'N')
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
		else
		{
			popText.push_back(std::make_unique<PopText>(readText, textX, textY, GetColor(255, 255, 255)));
			textX += 30;
			//popText[0] = readText[0];
			//popText[1] = readText[1];
		}

		waitTime += (readText[3] - '0') * 1000;
		waitTime += (readText[4] - '0') * 100;
		waitTime += (readText[5] - '0') * 10;
		waitTime += readText[6] - '0';
	}

	waitTime -= time->GetDeltaTime();
}
