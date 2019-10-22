#pragma once
#include"Notes.h"

class RepeatedNotes : public Notes
{
	int releaseTime;
	int longNotesHandle[3];
public:
	RepeatedNotes(int _notesHandle, int _releaseTime,int _longNotesHandle[]);

	void Update(int deltaTime);
	void Draw(int centerX, int centerY) const;

	void Push();
};