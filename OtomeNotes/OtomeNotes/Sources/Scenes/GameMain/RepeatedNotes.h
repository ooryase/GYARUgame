#pragma once
#include"Notes.h"

class RepeatedNotes : public Notes
{
	int releaseTime;
	int longNotesHandle;
	int fontHandle;
public:
	RepeatedNotes(int _notesHandle,int _krkrHandle, int _x, int _y, int _releaseTime,int _longNotesHandle,int _fontHandle);

	bool Update(int deltaTime,bool active);
	void Draw() const;

	void Push();
};