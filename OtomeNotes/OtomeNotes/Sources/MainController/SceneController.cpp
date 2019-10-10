#include<iostream>
#include"DxLib.h"
#include"SceneController.h"
#include"../Scenes/Title.h"

SceneController::SceneController()
{
	currentScene = std::make_shared<Title>();
}

int SceneController::SystemUpdate()
{
	currentScene->Update();

	DrawBegin();
	currentScene->Draw();
	DrawEnd();

	auto s = currentScene->GetNextScene();
	if (s != nullptr)
		currentScene = s;



	return 0;
}

void SceneController::DrawBegin()
{
	ClearDrawScreen();//裏画面消す
	SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に

}

void SceneController::DrawEnd()
{
	ScreenFlip();//裏画面を表画面にコピー
}

void SceneController::SceneChangeReservation(SceneType _nextScene)
{
	//nextScene = _nextScene;

}