#include<iostream>
#include"VirtualScene.h"

VirtualScene::VirtualScene()
{
	nextScene = nullptr;
}

std::shared_ptr<VirtualScene> VirtualScene::GetNextScene()
{
	return nextScene;
}