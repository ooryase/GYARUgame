#pragma once
#include"Notes.h"

class LongNotes : public Notes
{
	int releaseTime;
	int longNotesHandle[3];
public:
	LongNotes(int _notesHandle, int _releaseTime, int _longNotesHandle[]);

	void Update(int deltaTime);
	void Draw(int centerX, int centerY) const;

	void Push();
};