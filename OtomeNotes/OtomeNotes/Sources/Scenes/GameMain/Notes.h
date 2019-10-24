#pragma once

class Notes
{
protected:
	const int notesHandle;

public:
	enum EvalutionType
	{
		PERFECT,
		GOOD,
		BAD,
		DEFAULT
	};

	EvalutionType Evalution;

	bool Dead;
protected:

	int time;
	int popToJustTime; //ノーツ生成からジャストタイムまで(予兆)の時間
	bool push;

	EvalutionType NotesEvalution(int justTime);
public:
	Notes(int _notesHandle);

	virtual void Update(int deltaTime);
	virtual void Draw(int centerX, int centerY) const;

	virtual void Push();
};