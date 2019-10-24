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

	EvalutionType NotesEvalution(int justTime);
public:
	Notes(int _notesHandle);

	virtual void Update(int deltaTime);
	virtual void Draw(int centerX, int centerY) const;

	virtual void Push();
};