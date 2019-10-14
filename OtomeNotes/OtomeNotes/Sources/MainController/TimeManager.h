#pragma once

class TimeManager
{
private:
	int timeCount;
	int lastTime;
	int nowTime;

public:
	TimeManager();

	void TimeUpdate();
	//TimeCountの経過時間をリセットする
	void Reset();
	//1ループの経過時間をミリ秒単位で取得する
	int GetDeltaTime() const;
	//Resetされてからの経過時間をミリ秒単位で取得する
	int GetTimeCount() const;
};