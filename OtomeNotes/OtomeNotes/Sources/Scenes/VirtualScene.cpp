#include<iostream>
#include"VirtualScene.h"

VirtualScene::VirtualScene()
{
	nextScene = nullptr;
	time = std::make_shared<TimeManager>();
}

std::shared_ptr<VirtualScene> VirtualScene::GetNextScene()
{
	return nextScene;
}