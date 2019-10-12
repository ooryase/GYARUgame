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
	ChangeWindowMode(TRUE);

	//�E�B���h�E�T�C�Y���蓮�ł͕ύX�ł����A
	//���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	SetMainWindowText(TITLE);
	
	//��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�
	SetGraphMode(WinWidth, WinHeight, 32);

	//��ʃT�C�Y��ݒ�
	SetWindowSizeExtendRate(1, 0);

	//��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0xEF, 0xFF, 0xEF);

#pragma endregion 

	//Dx���C�u������������
	if (DxLib_Init() == -1)
	{
		//�G���[���o����}�C�i�X�l��Ԃ��ďI��
		return -1;
	}

	SceneController sceneController;

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		if (sceneController.SystemUpdate() != 0)
			break;


		//
		//�����ɖ��t���[���Ăԏ���������

		//
		WaitTimer(20);


	}
	//Dx���C�u�����I������
	DxLib_End();
	return 0;
}