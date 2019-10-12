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
	ClearDrawScreen();//����ʏ���
	SetDrawScreen(DX_SCREEN_BACK);//�`���𗠉�ʂ�

}

void SceneController::DrawEnd()
{
	ScreenFlip();//����ʂ�\��ʂɃR�s�[
}

void SceneController::SceneChangeReservation(SceneType _nextScene)
{
	//nextScene = _nextScene;

}