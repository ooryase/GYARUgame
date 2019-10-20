
class Notes
{
private:
	const int notesHandle;

public:
	enum class NotesType
	{
		NORMAL,
		LONG,
		REPEATED
	};

	enum class EvalutionType
	{
		PERFECT,
		GOOD,
		BAD,
		DEFAULT
	};

	EvalutionType Evalution;

	bool Dead;
private:
	NotesType notesType;

	int time;


public:
	Notes(NotesType _notesType,int _notesHandle);

	void Update(int deltaTime);

	void Draw(int centerX, int centerY) const;
};