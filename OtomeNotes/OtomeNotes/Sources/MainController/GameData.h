#pragma once

////Singleton
class GameData {

private:
	GameData() {}
	GameData(const GameData&) = delete;
	GameData& operator = (const GameData&) = delete;

public:
	int Score;
	int Stage;

	static GameData& getInstance();

	void Init();
};