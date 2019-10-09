#include "DxLib.h"
#include <stdio.h>

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	const char TITLE[] = "石崎_01_Step2"; //もう変更されない

	int WinWidth = 1920;
	int WinHeight = 1080;

	int MapWidth = 640;
	int MapHeight = 400;

	int Cr = GetColor(255, 255, 255);
	const int Minus = 50;
	SetFontSize(16);

	int positionX = 300;
	int velocityX = 1;
	int positionY = 300;
	int velocityY = 1;

	bool drawFlag = 0;
	bool trigger = 0;
#pragma region 初期処理

	//ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	//ウィンドウサイズを手動では変更できず、
	//かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	SetMainWindowText(TITLE);
	
	//画面サイズの最大サイズ、カラービット数を設定
	SetGraphMode(MapWidth, MapHeight, 32);

	//画面サイズを設定
	SetWindowSizeExtendRate(1, 0);

	//画面の背景色を設定する
	SetBackgroundColor(0, 0, 0);

#pragma endregion 

	//Dxライブラリを初期化
	if (DxLib_Init() == -1)
	{
		//エラーが出たらマイナス値を返して終了
		return -1;
	}

	while (true)
	{
		WaitTimer(20);
		if (ProcessMessage() == -1) break; //WIndowsAPIのエラー処理
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;

		if (CheckHitKey(KEY_INPUT_SPACE) == 1 && drawFlag == 0 && trigger == 0)
		{
			drawFlag = 1;
			trigger = 1;
		}
		else if (CheckHitKey(KEY_INPUT_SPACE) == 1 && trigger == 0)
		{
			drawFlag = 0;
			trigger = 1;
		}
		else if(CheckHitKey(KEY_INPUT_SPACE) == 0) trigger = 0;

		if (drawFlag == 1) ClearDrawScreen();

		DrawString(10, 10, "SPACE : 描画のON / OFF", Cr, 0);
		DrawBox(Minus, Minus, MapWidth - Minus, MapHeight - Minus, Cr, 0);

		if (positionX > MapWidth - Minus || positionX < Minus) velocityX *= -1;

		if (positionY > MapHeight - Minus || positionY < Minus) velocityY *= -1;

		positionX += velocityX;
		positionY += velocityY;

		DrawPixel(positionX, positionY, Cr);
	}

	//Dxライブラリ終了処理
	DxLib_End();
	return 0;
}