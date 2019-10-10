#include"GameData.h"

GameData& GameData::getInstance()
{
	static GameData instance;
	return instance;
}

void GameData::Init()
{
	Score = 0;
}