#include"DxLib.h"
#include<iostream>
#include <algorithm>

#include"GameMain.h"
#include"../Particles/EvalutionText.h"


GameMain::GameMain() : VirtualScene(),
	fileHandle(FileRead_open("Assets/CSV/Notes.csv")),
	fontHandle(LoadFontDataToHandle("Assets/Fonts/Senobi_m.dft",1)),
	buttonHandle(LoadGraph("Assets/Textures/GameMain/Button.png")),
	notesHandle(LoadGraph("Assets/Textures/GameMain/Notes.png")),
	osakabechankariHandle(LoadGraph("Assets/Textures/GameMain/Osakabechankari.png")),
	roomHandle(LoadGraph("Assets/Textures/GameMain/room.jpg")),
	textFrameHandle(LoadGraph("Assets/Textures/GameMain/TextFrame.png"))
{
	waitTime = 0;

	textX = 200;
	textY = 600;

	score = 0;
}

GameMain::~GameMain()
{
	FileRead_close(fileHandle);
	DeleteFontToHandle(fontHandle);
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
			switch (var->Evalution)
			{
			case Notes::EvalutionType::GOOD:
				score += 1000;
				particles.push_back(std::make_shared<EvalutionText>(800, 680, fontHandle, "GOOD"));
				break;
			case Notes::EvalutionType::PERFECT:
				score += 2000;
				particles.push_back(std::make_shared<EvalutionText>(800, 680, fontHandle, "PERFECT"));
				break;
			case Notes::EvalutionType::BAD:
				score += 50;
				particles.push_back(std::make_shared<EvalutionText>(800, 680, fontHandle, "BAD"));
				break;
			}
			var->Evalution = Notes::EvalutionType::DEFAULT;
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
}

void GameMain::TextRead()
{
	if (waitTime <= 0 && !FileRead_eof(fileHandle))
	{
		FileRead_gets(readText, 256, fileHandle);
		//		waitTime = 1300;

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

		if (readText[0] == 'N')
		{
			switch (readText[1])
			{
			case 'N':
				notes.push_back(std::make_shared<Notes>(Notes::NotesType::NORMAL, notesHandle));
				break;
			case 'L':

				break;
			case 'P':

				break;
			default:
				break;
			}
		}
		else
		{
			popText.push_back(std::make_unique<PopText>(readText, textX, textY));
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
