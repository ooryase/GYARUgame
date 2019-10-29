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
	int BgmHandle;//�V�[�����܂����ōĐ��������鎞�p

	static GameData& getInstance();

	void Init();
};