#pragma once


class Button
{
private:
	int time;
	const int baseX, baseY;
	const int notesPopToJustTime;
	int texHandle[2];
	bool end;
	int endTimer;

public:
	bool Dead;

	Button(int _texHandle[], int _popToJustTime);

	void Update(int deltaTime);
	void Draw() const;

	void End();

	int GetTime() const;

	//旧ボタンは新ボタン発生後
	//810ms (popToJustTimeからBad判定時間だけ引いた値)まで判定基準となるが、
	//以後は表示されるのみとなる
	bool NotActive() const;
};