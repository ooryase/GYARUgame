#pragma once

class Notes
{
protected:
	const int notesHandle;
	const int krkrHandle;

public:
	enum EvalutionType
	{
		PERFECT,
		GOOD,
		BAD,
		MISS,
		DEFAULT
	};

	EvalutionType Evalution;

	bool Dead;
protected:

	int time;
	int popToJustTime; //ノーツ生成からジャストタイムまで(予兆)の時間
	bool push;
	int x, y;

	EvalutionType NotesEvalution(int justTime);
public:
	Notes(int _notesHandle,int _krkrHandle,int _x,int _y);

	virtual bool Update(int deltaTime, bool active);
	virtual void Draw() const;

	virtual void Push();
};