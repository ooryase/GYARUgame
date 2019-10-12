#include "DxLib.h"
#include <stdio.h>
#include"SceneController.h"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	const char TITLE[] = "オトメノーツ"; //もう変更されない

	int WinWidth = 1280;
	int WinHeight = 720;

	int MapWidth = 640;
	int MapHeight = 480;

#pragma region 初期処理

	//ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	//ウィンドウサイズを手動では変更できず、
	//かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	SetMainWindowText(TITLE);
	
	//画面サイズの最大サイズ、カラービット数を設定
	SetGraphMode(WinWidth, WinHeight, 32);

	//画面サイズを設定
	SetWindowSizeExtendRate(1, 0);

	//画面の背景色を設定する
	SetBackgroundColor(0xEF, 0xFF, 0xEF);

#pragma endregion 

	//Dxライブラリを初期化
	if (DxLib_Init() == -1)
	{
		//エラーが出たらマイナス値を返して終了
		return -1;
	}

	SceneController sceneController;

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		if (sceneController.SystemUpdate() != 0)
			break;


		//
		//ここに毎フレーム呼ぶ処理を書く

		//
		WaitTimer(20);


	}
	//Dxライブラリ終了処理
	DxLib_End();
	return 0;
}