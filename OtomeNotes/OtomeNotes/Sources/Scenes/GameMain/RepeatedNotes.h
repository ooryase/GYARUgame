#pragma once
#include"Notes.h"

class RepeatedNotes : public Notes
{
	int releaseTime;
	int longNotesHandle[3];
public:
	RepeatedNotes(int _notesHandle, int _x, int _y, int _releaseTime,int _longNotesHandle[]);

	void Update(int deltaTime);
	void Draw() const;

	void Push();
};