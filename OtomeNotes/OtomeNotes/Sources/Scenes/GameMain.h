#include<vector>
#include"VirtualScene.h"
#include"../MainController/TimeManager.h"


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

	class PopText
	{
	private:
		int time;
		char text[256];
		int x, baseX, y, baseY;

	public:
		PopText(char* _text, int _x, int _y);

		void Update(std::shared_ptr<TimeManager> timeManager);
		void Draw(int fontHandle) const;

		bool Dead();
	};

	std::vector<std::unique_ptr<PopText>> popText;

public:
	GameMain();
	~GameMain();

	void Update();
	void Draw() const;
};