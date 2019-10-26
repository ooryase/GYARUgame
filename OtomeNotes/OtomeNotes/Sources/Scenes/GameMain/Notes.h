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
	int x, y;

	EvalutionType NotesEvalution(int justTime);
public:
	Notes(int _notesHandle,int _x,int _y);

	virtual void Update(int deltaTime);
	virtual void Draw() const;

	virtual void Push();
};