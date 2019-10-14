#include<iostream>
#include"VirtualScene.h"

VirtualScene::VirtualScene()
{
	nextScene = nullptr;
	time = TimeManager();
}

std::shared_ptr<VirtualScene> VirtualScene::GetNextScene()
{
	return nextScene;
}