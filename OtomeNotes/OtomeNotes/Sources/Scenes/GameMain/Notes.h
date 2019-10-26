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
	int popToJustTime; //�m�[�c��������W���X�g�^�C���܂�(�\��)�̎���
	bool push;
	int x, y;

	EvalutionType NotesEvalution(int justTime);
public:
	Notes(int _notesHandle,int _x,int _y);

	virtual void Update(int deltaTime);
	virtual void Draw() const;

	virtual void Push();
};