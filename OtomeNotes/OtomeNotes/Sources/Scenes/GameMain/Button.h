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

	//���{�^���͐V�{�^��������
	//810ms (popToJustTime����Bad���莞�Ԃ����������l)�܂Ŕ����ƂȂ邪�A
	//�Ȍ�͕\�������݂̂ƂȂ�
	bool NotActive() const;
};