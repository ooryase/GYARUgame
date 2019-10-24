#include<vector>
#include<queue>
#include"VirtualScene.h"
#include"GameMain/Notes.h"
#include"GameMain/LongNotes.h"
#include"GameMain/RepeatedNotes.h"
#include"GameMain/PopText.h"
#include"../MainController/TimeManager.h"
#include"../Particles/VirtualParticle.h"
#include"../Particles/EvalutionText.h"
#include"../Particles/NotesButton.h"

class GameMain : public VirtualScene
{
private:
	const int modelHandle;
	const int fileHandle;
	const int fontHandle;
	const int buttonHandle;
	int notesHandle[3];
	int LongNotesHandle[3];
	const int osakabechankariHandle;
	const int roomHandle;
	const int textFrameHandle;
	const int SE_notesHandle;

	int waitTime;
	char readText[256];
	int popToJustTime; //ノーツ生成からジャストタイムまで(予兆)の時間
	class CharClass { public: char Text[256]; CharClass(char* _text); };
	std::queue<CharClass> waitTextQueue;
	int textQueueWaitTime;

	//char popText[2];
	int textX, textY; //テキストの1文字目の座標
	int notesX, notesY; //ノーツの座標

	std::vector<std::shared_ptr<PopText>> popText;
	std::vector<std::shared_ptr<Notes>> notes;

	std::vector<std::shared_ptr<VirtualParticle>> particles;

	int score;
public:
	GameMain();
	~GameMain();

	void Update();
	void Draw() const;

private:
	void CSVRead();
	void QueueRead();
	void NotesPush(char _notesType);
};