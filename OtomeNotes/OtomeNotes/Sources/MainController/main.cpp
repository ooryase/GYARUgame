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
	const char TITLE[] = "�I�g���m�[�c"; //�����ύX����Ȃ�

	int WinWidth = 1280;
	int WinHeight = 720;

	int MapWidth = 640;
	int MapHeight = 480;



#pragma region ��������

	//�E�B���h�E���[�h�ɐݒ�
#if _DEBUG
	ChangeWindowMode(TRUE);
#else
	ChangeWindowMode(FALSE);
#endif

	//�E�B���h�E�T�C�Y���蓮�ł͕ύX�ł����A
	//���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	SetMainWindowText(TITLE);

	//��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�
	SetGraphMode(WinWidth, WinHeight, 32);

	//��ʃT�C�Y��ݒ�
	SetWindowSizeExtendRate(1, 0);

	//��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0xFF, 0xFF, 0xFF);

#pragma endregion 

	// Live2D Cubism Core DLL �̓ǂݍ���( 64bit �A�v���̏ꍇ�� 32bit �A�v���̏ꍇ�œǂݍ��� dll ��ύX )
#ifdef _WIN64
	Live2D_SetCubism4CoreDLLPath("Assets/Live2d/dll/x86_64/Live2DCubismCore.dll");
#else
	Live2D_SetCubism4CoreDLLPath("Assets/Live2d/dll/x86/Live2DCubismCore.dll");
#endif

	// �c�w���C�u��������������
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

	// Live2D���f���̓ǂݍ���
	/*int ModelHandle = Live2D_LoadModel("Assets/Live2d/Hiyori/Hiyori.model3.json");

	// �`���𗠉�ʂɕύX
	SetDrawScreen(DX_SCREEN_BACK);

	// ���C�����[�v
	while (ProcessMessage() == 0)
	{
		// ��ʂ̏�����
		ClearDrawScreen();

		// ���[�V�����Đ����I�����Ă�����A�C�h�����O���[�V�����������_���ōĐ�
		if (Live2D_Model_IsMotionFinished(ModelHandle) == TRUE)
		{
			Live2D_Model_StartMotion(ModelHandle, "Idle", GetRand(8));
		}

		// ���f���̏�Ԃ�60����1�b���i�߂�
		Live2D_Model_Update(ModelHandle, 1 / 60.0f);

		// Live2D�`��̊J�n
		Live2D_RenderBegin();

		// ���f���̕`��
		Live2D_Model_Draw(ModelHandle);

		// Live2D�`��̏I��
		Live2D_RenderEnd();

		DrawString(0, 0, "TESTESTEST", GetColor(255, 255, 255));

		// ����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}

	// Live2D ���f���̍폜
	Live2D_DeleteModel(ModelHandle);*/

	// �c�w���C�u�����g�p�̏I������
	DxLib_End();

	// �\�t�g�̏I��
	return 0;



}