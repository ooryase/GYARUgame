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
	//���[�h�n���h��
	const int modelHandle;
	int fileHandle;
	const int fontHandle;
	const int buttonHandle;
	int notesHandle[3];
	int LongNotesHandle[3];
	int charaHandle;
	int backGroundHandle[3];
	const int textFrameHandle;
	const int SE_notesHandle;
	int bgmHandle;
	int fullTextHandle[3];
	int krkrHandle;
	const int gaugeHandle;
	const int gaugeHandle2;

	//CSV���[�h�Ǘ�
	int waitTime;
	char readText[256];
	int popToJustTime; //�m�[�c��������W���X�g�^�C���܂�(�\��)�̎���
	class CharClass { public: char Text[256]; CharClass(char* _text); };
	std::queue<CharClass> waitTextQueue;
	int textQueueWaitTime;

	//�m�[�c�`��Ǘ�
	int textX, textY; //�e�L�X�g�̐������W
	int notesX, notesY; //�m�[�c�̐������W
	int buttonXTimer; //�{�^���̍��W��̃^�C�}�\

	//�w�i�Ǘ�
	int backGroundStep;

	//�z��Ǘ�
	std::vector<std::shared_ptr<PopText>> popText;
	std::vector<std::shared_ptr<Notes>> notes;
	std::vector<std::shared_ptr<VirtualParticle>> particles;
	std::vector<std::shared_ptr<Button>> buttons;

	//�X�R�A�Ǘ�
	int score;
	int scoreCount[3];
	int feel;
	bool fever;

	//���U���g�p�ϐ�
	int scorePopCount;

	//�t�F�[�Y�Ǘ�
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

	void CSVRead();
	void QueueRead();
	void NotesPush(char _notesType);

	void AddFeel(int addFeel);

	template <typename T> void UpdateAndDelete(std::vector<T>&& t, int deltaTime);
};