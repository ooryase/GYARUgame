#include"DxLib.h"
#include"TimeManager.h"

TimeManager::TimeManager()
{
	timeCount = 0;
	lastTime = nowTime = GetNowCount();
}

void TimeManager::TimeUpdate()
{
	lastTime = nowTime;
	nowTime = GetNowCount();
	timeCount += nowTime - lastTime;
}

void TimeManager::Reset()
{
	timeCount = 0;
}

int TimeManager::GetDeltaTime() const
{
	return nowTime - lastTime;
}

int TimeManager::GetTimeCount() const
{
	return timeCount;
}