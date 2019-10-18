
class Notes
{
public:
	enum class NotesType
	{
		NORMAL,
		LONG,
		REPEATED
	};

	enum class Evalution
	{
		PERFECT,
		GOOD,
		BAD,
		NULL
	};
private:
	NotesType notesType;

	int time;



public:
	Notes();
};