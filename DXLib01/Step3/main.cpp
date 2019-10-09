#include "DxLib.h"
#include <stdio.h>

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	const char TITLE[] = "�΍�_01_Step3"; //�����ύX����Ȃ�

	int WinWidth = 1920;
	int WinHeight = 1080;

	int MapWidth = 640;
	int MapHeight = 400;

	int Cr[3] = { GetColor(200, 133, 63), GetColor(224, 123, 63), GetColor(255, 103, 63) };
	int CrCurrent = GetColor(224, 133, 63); //���݂̐F
	const int Minus = 50;

	int pX[3] = { 300, 300, 300 };
	int vX[3] = { 3, -1, 2 };
	int pY[3] = { 300, 300, 300 };
	int vY[3] = { 3, -1, 2 }; //Position��Velocity�R����

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
	SetBackgroundColor(211, 160, 211);

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

		ClearDrawScreen(); //1�O�̎O�p�`������

		DrawBox(Minus, Minus, MapWidth - Minus, MapHeight - Minus, GetColor(255, 255, 255), 0);

		for (int i = 0; i < 3; i++)
		{
			if (pX[i] > MapWidth - Minus || pX[i] < Minus)
			{
				vX[i] *= -1;
				CrCurrent = Cr[i]; //�Ԃ��������_�̐F�ɕύX
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

	//Dx���C�u�����I������
	DxLib_End();
	return 0;
}