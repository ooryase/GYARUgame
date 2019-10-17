#include"DxLib.h"
#include"GameMain.h"
#include<iostream>


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
	popText.clear();

	textX = 200;
	textY = 500;

}

GameMain::~GameMain()
{
	FileRead_close(fileHandle);
	DeleteFontToHandle(fontHandle);
}


void GameMain::Update()
{
	time->TimeUpdate();

	if (waitTime <= 0 && !FileRead_eof(fileHandle))
	{
		FileRead_gets(readText, 256, fileHandle);
		waitTime = 1300;

		popText.push_back(std::make_unique<PopText>(readText, textX, textY));
		textX += 30;
		//popText[0] = readText[0];
		//popText[1] = readText[1];

		waitTime = (readText[3] - '0') * 1000;
		waitTime += (readText[4] - '0') * 100;
		waitTime += (readText[5] - '0') * 10;
		waitTime += readText[6] - '0';

	}

	for (auto&& var : popText)
	{
		var->Update(time);
	}

	waitTime -= time->GetDeltaTime();
	
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


}

GameMain::PopText::PopText(char* _text,int _x,int _y)
{
	std::memset(text, 0, sizeof(text));
	text[0] = _text[0];
	text[1] = _text[1];


	time = 0;
	x = baseX = _x;
	y = baseY = _y;
}

void GameMain::PopText::Update(std::shared_ptr<TimeManager> timeManager)
{
	time += timeManager->GetDeltaTime();

	if (time < 300)
		y = baseY - static_cast<int>((300 - time) * time / (255.0 * 255.0) * 30.0);
	else
		y = baseY;
}

void GameMain::PopText::Draw(int fontHandle) const
{
	DrawStringToHandle(x, y, text, GetColor(255, 255, 255),fontHandle);
}

bool GameMain::PopText::Dead()
{
	return false;
}