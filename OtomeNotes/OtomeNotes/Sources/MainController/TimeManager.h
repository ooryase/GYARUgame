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
	//TimeCount�̌o�ߎ��Ԃ����Z�b�g����
	void Reset();
	//1���[�v�̌o�ߎ��Ԃ��~���b�P�ʂŎ擾����
	int GetDeltaTime() const;
	//Reset����Ă���̌o�ߎ��Ԃ��~���b�P�ʂŎ擾����
	int GetTimeCount() const;
};