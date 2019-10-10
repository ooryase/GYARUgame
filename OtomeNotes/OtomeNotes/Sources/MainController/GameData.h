#pragma once

////Singleton
class GameData {

private:
	GameData() {}
	GameData(const GameData&) = delete;
	GameData& operator = (const GameData&) = delete;

	int Score;
public:
	static GameData& getInstance();

	void Init();
};