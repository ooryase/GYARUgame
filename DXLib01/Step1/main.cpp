#include "DxLib.h"
#include <stdio.h>

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	const char TITLE[] = "�΍�_01_Step1"; //�����ύX����Ȃ�

	int WinWidth = 1920;
	int WinHeight = 1080;

	int MapWidth = 640;
	int MapHeight = 480;

	int CrGreen = GetColor(47, 255, 47);
	int CrGreen2 = GetColor(142, 255, 0);
	int CrGreenDeep = GetColor(154, 205, 50);
	int CrGreenLight = GetColor(152, 205, 212);
	int CrBlue = GetColor(0, 191, 255);

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

	while (true)
	{
		WaitTimer(20);
		if (ProcessMessage() == -1) break; //WIndowsAPI�̃G���[����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;

		DrawLine(400, 100, 500, 400, CrGreen, 30); //��	

		DrawBox(100, 100, 600, 150, CrGreenDeep, 1); //�l�p

		DrawTriangle(50, 400, 200, 70, 170, 300, CrGreenLight, 1); //�O�p

		DrawCircle(MapWidth / 2, MapHeight / 2, 30, CrGreen2, 0); //��

		DrawOval(400, 350, 60, 30, CrBlue, 1); //�ȉ~
	}

	//Dx���C�u�����I������
	DxLib_End();
	return 0;
}