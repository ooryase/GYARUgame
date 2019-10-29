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
#if _DEBUG
	ChangeWindowMode(TRUE);
#else
	ChangeWindowMode(FALSE);
#endif

	//ウィンドウサイズを手動では変更できず、
	//かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	SetMainWindowText(TITLE);

	//画面サイズの最大サイズ、カラービット数を設定
	SetGraphMode(WinWidth, WinHeight, 32);

	//画面サイズを設定
	SetWindowSizeExtendRate(1, 0);

	//画面の背景色を設定する
	SetBackgroundColor(0xFF, 0xFF, 0xFF);

#pragma endregion 

	// Live2D Cubism Core DLL の読み込み( 64bit アプリの場合と 32bit アプリの場合で読み込む dll を変更 )
#ifdef _WIN64
	Live2D_SetCubism4CoreDLLPath("Assets/Live2d/dll/x86_64/Live2DCubismCore.dll");
#else
	Live2D_SetCubism4CoreDLLPath("Assets/Live2d/dll/x86/Live2DCubismCore.dll");
#endif

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	SceneController sceneController;

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		if (sceneController.SystemUpdate() != 0)
			break;

		//
		//WaitTimer(20);


	}

	// Live2Dモデルの読み込み
	/*int ModelHandle = Live2D_LoadModel("Assets/Live2d/Hiyori/Hiyori.model3.json");

	// 描画先を裏画面に変更
	SetDrawScreen(DX_SCREEN_BACK);

	// メインループ
	while (ProcessMessage() == 0)
	{
		// 画面の初期化
		ClearDrawScreen();

		// モーション再生が終了していたらアイドリングモーションをランダムで再生
		if (Live2D_Model_IsMotionFinished(ModelHandle) == TRUE)
		{
			Live2D_Model_StartMotion(ModelHandle, "Idle", GetRand(8));
		}

		// モデルの状態を60分の1秒分進める
		Live2D_Model_Update(ModelHandle, 1 / 60.0f);

		// Live2D描画の開始
		Live2D_RenderBegin();

		// モデルの描画
		Live2D_Model_Draw(ModelHandle);

		// Live2D描画の終了
		Live2D_RenderEnd();

		DrawString(0, 0, "TESTESTEST", GetColor(255, 255, 255));

		// 裏画面の内容を表画面に反映
		ScreenFlip();
	}

	// Live2D モデルの削除
	Live2D_DeleteModel(ModelHandle);*/

	// ＤＸライブラリ使用の終了処理
	DxLib_End();

	// ソフトの終了
	return 0;



}