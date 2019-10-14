#include<iostream>
#include"DxLib.h"
#include"StageSelect.h"
#include"../MainController/InputController.h"
#include"Title.h"


StageSelect::StageSelect()
{
	stageImageHandle.push_back(LoadGraph("Assets/Textures/StageSelect/Stage1.jpg"));
	stageImageHandle.push_back(LoadGraph("Assets/Textures/StageSelect/Stage2.jpg"));
	stageImageHandle.push_back(LoadGraph("Assets/Textures/StageSelect/Stage3.png"));

	radian = 0.0;
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

	radian += time.GetDeltaTime() * 0.0011;

	if (InputController::getInstance().GetPush(KEY_INPUT_Z))
	{
		nextScene = std::make_shared<Title>();
	}
}

void StageSelect::Draw() const
{
	auto size = static_cast<double>(stageImageHandle.size());
	int x, y, c;
	GetScreenState(&x, &y, &c);
	double PI = 3.14159265358979323846;

	for (int i = 0; i < size; i++)
	{

		DrawGraph( x / 2 + static_cast<int>( (x / 4) * std::cos(radian + 2.0 * PI * (i / size))) - 150,
			y / 2 + static_cast<int>( (y / 8) * std::sin(radian + 2.0 * PI * (i / size))) - 230,
			stageImageHandle.at(i), TRUE);
	}

}