#pragma once
#include"Notes.h"

class RepeatedNotes : public Notes
{
	int releaseTime;
	int longNotesHandle;
public:
	RepeatedNotes(int _notesHandle,int _krkrHandle, int _x, int _y, int _releaseTime,int _longNotesHandle);

	bool Update(int deltaTime,bool active);
	void Draw() const;

	void Push();
};