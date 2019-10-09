#include "DxLib.h"
#include <stdio.h>

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	const char TITLE[] = "石崎_01_Step3"; //もう変更されない

	int WinWidth = 1920;
	int WinHeight = 1080;

	int MapWidth = 640;
	int MapHeight = 400;

	int Cr[3] = { GetColor(200, 133, 63), GetColor(224, 123, 63), GetColor(255, 103, 63) };
	int CrCurrent = GetColor(224, 133, 63); //現在の色
	const int Minus = 50;

	int pX[3] = { 300, 300, 300 };
	int vX[3] = { 3, -1, 2 };
	int pY[3] = { 300, 300, 300 };
	int vY[3] = { 3, -1, 2 }; //PositionとVelocity３つずつ

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
	SetBackgroundColor(211, 160, 211);

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

		ClearDrawScreen(); //1つ前の三角形を消す

		DrawBox(Minus, Minus, MapWidth - Minus, MapHeight - Minus, GetColor(255, 255, 255), 0);

		for (int i = 0; i < 3; i++)
		{
			if (pX[i] > MapWidth - Minus || pX[i] < Minus)
			{
				vX[i] *= -1;
				CrCurrent = Cr[i]; //ぶつかった頂点の色に変更
			}

			if (pY[i] > MapHeight - Minus || pY[i] < Minus)
			{
				vY[i] *= -1;
				CrCurrent = Cr[i];
			}

			pX[i] += vX[i];
			pY[i] += vY[i];
		}

		DrawTriangle(pX[0], pY[0], pX[1], pY[1], pX[2], pY[2], CrCurrent, 1);
	}

	//Dxライブラリ終了処理
	DxLib_End();
	return 0;
}