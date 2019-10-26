#include<vector>
#include<queue>
#include"VirtualScene.h"
#include"GameMain/Notes.h"
#include"GameMain/LongNotes.h"
#include"GameMain/RepeatedNotes.h"
#include"GameMain/PopText.h"
#include"GameMain/Button.h"
#include"../MainController/TimeManager.h"
#include"../Particles/VirtualParticle.h"
#include"../Particles/EvalutionText.h"
#include"../Particles/NotesButton.h"
#include"../Particles/Krkr.h"

class GameMain : public VirtualScene
{
private:
	//ロードハンドル
	const int modelHandle;
	int fileHandle;
	const int fontHandle;
	const int buttonHandle;
	int notesHandle[3];
	const int longNotesHandle;
	int charaHandle;
	int backGroundHandle[3];
	const int textFrameHandle;
	const int SE_notesHandle;
	int bgmHandle;
	int fullTextHandle[3];
	int feverBackHandle[2];
	int krkrHandle;
	int hwhwHandle;
	const int gaugeHandle;
	const int gaugeHandle2;

	//CSVロード管理
	int waitTime;
	char readText[256];
	int popToJustTime; //ノーツ生成からジャストタイムまで(予兆)の時間
	class CharClass { public: char Text[256]; CharClass(char* _text); };
	std::queue<CharClass> waitTextQueue;
	int textQueueWaitTime;

	//ノーツ描画管理
	int textX, textY; //テキストの生成座標
	int notesX, notesY; //ノーツの生成座標

	//背景管理
	int backGroundStep;

	//配列管理
	std::vector<std::shared_ptr<PopText>> popText;
	std::vector<std::shared_ptr<Notes>> notes;
	std::vector<std::shared_ptr<VirtualParticle>> particles;
	std::vector<std::shared_ptr<Button>> buttons;

	//スコア管理
	int score;
	int scoreCount[3];
	int scoreColor[3];
	int feel;
	int fever;
	int feverTime;

	//リザルト用変数
	int scorePopCount;

	//フェーズ管理
	enum class PhaseType
	{
		START,
		MAIN,
		RESULT
	};
	PhaseType phase;

public:
	GameMain();
	~GameMain();

	void Update();
	void Draw() const;

private:
	void LoadSelectChara();

	void StartUpdate();
	void MainUpdate();
	void ResultUpdate();

	void StartDraw() const;
	void MainDraw() const;
	void ResultDraw() const;

	void GaugeDraw(int x,int y) const;
	void FeverDraw(int x, int y) const;

	void CSVRead();
	void QueueRead();
	void NotesPush(char _notesType);

	void AddFeel(int addFeel);
	//scoreCountの番号、分子、分母
	std::string ScoreCountTostring(int num, int numerator,int denominator) const;

	template <typename T> void UpdateAndDelete(std::vector<T>&& t, int deltaTime);
};