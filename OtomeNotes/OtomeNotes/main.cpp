#include "DxLib.h"
#include <stdio.h>

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	const char TITLE[] = "�I�g���m�[�c"; //�����ύX����Ȃ�

	int WinWidth = 1920;
	int WinHeight = 1080;

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
	SetGraphMode(MapWidth, MapHeight, 32);

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

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();//����ʏ���
		SetDrawScreen(DX_SCREEN_BACK);//�`���𗠉�ʂ�

		//
		//�����ɖ��t���[���Ăԏ���������
		//
		WaitTimer(20);

		ScreenFlip();//����ʂ�\��ʂɃR�s�[

	}
	//Dx���C�u�����I������
	DxLib_End();
	return 0;
}