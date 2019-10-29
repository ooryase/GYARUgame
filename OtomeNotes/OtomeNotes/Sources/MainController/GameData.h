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
	int BgmHandle;//シーンをまたいで再生し続ける時用

	static GameData& getInstance();

	void Init();
};