#include "DxLib.h"
#include <stdio.h>

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	const char TITLE[] = "石崎_01_Step1"; //もう変更されない

	int WinWidth = 1920;
	int WinHeight = 1080;

	int MapWidth = 640;
	int MapHeight = 480;

	int CrGreen = GetColor(47, 255, 47);
	int CrGreen2 = GetColor(142, 255, 0);
	int CrGreenDeep = GetColor(154, 205, 50);
	int CrGreenLight = GetColor(152, 205, 212);
	int CrBlue = GetColor(0, 191, 255);

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
	SetBackgroundColor(0xEF, 0xFF, 0xEF);

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

		DrawLine(400, 100, 500, 400, CrGreen, 30); //線	

		DrawBox(100, 100, 600, 150, CrGreenDeep, 1); //四角

		DrawTriangle(50, 400, 200, 70, 170, 300, CrGreenLight, 1); //三角

		DrawCircle(MapWidth / 2, MapHeight / 2, 30, CrGreen2, 0); //丸

		DrawOval(400, 350, 60, 30, CrBlue, 1); //楕円
	}

	//Dxライブラリ終了処理
	DxLib_End();
	return 0;
}