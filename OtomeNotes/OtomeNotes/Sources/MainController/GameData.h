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
	int BgmHandle;//ƒV[ƒ“‚ğ‚Ü‚½‚¢‚ÅÄ¶‚µ‘±‚¯‚é—p

	static GameData& getInstance();

	void Init();
};