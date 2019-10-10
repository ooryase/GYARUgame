#pragma once
#include<iostream>
#include"../Scenes/VirtualScene.h"

class SceneController
{
private:
	std::shared_ptr<VirtualScene> currentScene;

public:
	enum class SceneType
	{
		Title,
		GameMain,
		Result
	};

public:
	SceneController();

	int SystemUpdate();

private:
	void DrawBegin();
	void DrawEnd();

public:
	void SceneChangeReservation(SceneType _nextSceneType);
};