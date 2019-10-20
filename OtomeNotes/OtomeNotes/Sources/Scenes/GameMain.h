#include<vector>
#include"VirtualScene.h"
#include"GameMain/Notes.h"
#include"GameMain/PopText.h"
#include"../MainController/TimeManager.h"
#include"../Particles/VirtualParticle.h"

class GameMain : public VirtualScene
{
private:
	const int fileHandle;
	const int fontHandle;
	const int buttonHandle;
	const int notesHandle;
	const int osakabechankariHandle;
	const int roomHandle;
	const int textFrameHandle;

	int waitTime;
	char readText[256];
	//char popText[2];
	int textX, textY;

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
	void TextRead();
};