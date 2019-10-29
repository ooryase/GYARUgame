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
#include"../Particles/Hwhw.h"
#include"../Particles/Doyon.h"

class GameMain : public VirtualScene
{
private:
	////���[�h�n���h��

	//Live2d���f��
	int modelHandle;

	//�t�@�C��
	int fileHandle;

	//�t�H���g
	const int fontHandle;
	const int mFontHandle;
	const int largeFontHandle;

	//�e�N�X�`��
	int buttonHandle[2];
	int notesHandle[3];
	const int longNotesHandle;
	int backGroundHandle[3];
	const int textFrameHandle;
	const int frameHandle;
	int fullTextHandle[3];
	int feverBackHandle[2];
	int krkrHandle;
	int hwhwHandle[4];
	const int gaugeHandle;
	const int gaugeHandle2;
	const int heartHandle;

	//�T�E���h
	const int SE_notesHandle;
	int resultVoiceHandle[3];
	int bgmHandle;
	const int bgmResultHandle;
	const int reStartHandle;

	////CSV���[�h�Ǘ�
	int waitTime;
	char readText[256];
	int popToJustTime; //�m�[�c��������W���X�g�^�C���܂�(�\��)�̎���
	class CharClass { public: char Text[256]; CharClass(char* _text); };
	std::queue<CharClass> waitTextQueue;
	int textQueueWaitTime;

	////�m�[�c�`��Ǘ�
	int textX, textY; //�e�L�X�g�̐������W
	int notesX, notesY; //�m�[�c�̐������W

	////�w�i�Ǘ�
	int backGroundStep;
	int backGroundTime;

	////�z��Ǘ�
	std::vector<std::shared_ptr<PopText>> popText;
	std::vector<std::shared_ptr<Notes>> notes;
	std::vector<std::shared_ptr<VirtualParticle>> particles;
	std::vector<std::shared_ptr<VirtualParticle>> backParticles;
	std::vector<std::shared_ptr<Button>> buttons;

	////�X�R�A�Ǘ�
	int score;
	int scoreCount[4];
	int scoreColor[4];
	int lastFeel;
	int feel;
	int fever;
	int feverTime;
	int pushTime;
	std::string scoreName[4];

	////���U���g�p�ϐ�
	int scorePopCount;
	int pressTime;

	////�t�F�[�Y�Ǘ�
	enum class PhaseType
	{
		START,
		MAIN,
		RESULT,
		NEXT
	};
	PhaseType phase;

	//�L�����̖��O
	std::string charaName;

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
	void NextUpdate();

	void StartDraw() const;
	void MainDraw() const;
	void ResultDraw() const;
	void NextDraw() const;

	void GaugeDraw(int x,int y) const;
	void FeverDraw(int x, int y) const;

	void ScoreDraw(int x, int y) const;

	void CSVRead();
	void QueueRead();
	void NotesPush(char _notesType);
	void NotesCheck();

	void AddFeel(int addFeel);
	//scoreCount�̔ԍ��A���q�A����
	std::string ScoreCountTostring(int num, int numerator,int denominator) const;

	template <typename T> void UpdateAndDelete(std::vector<T>&& t, int deltaTime);
};