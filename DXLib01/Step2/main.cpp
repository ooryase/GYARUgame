#include "DxLib.h"
#include <stdio.h>

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	const char TITLE[] = "�΍�_01_Step2"; //�����ύX����Ȃ�

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
	SetBackgroundColor(0, 0, 0);

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

		DrawString(10, 10, "SPACE : �`���ON / OFF", Cr, 0);
		DrawBox(Minus, Minus, MapWidth - Minus, MapHeight - Minus, Cr, 0);

		if (positionX > MapWidth - Minus || positionX < Minus) velocityX *= -1;

		if (positionY > MapHeight - Minus || positionY < Minus) velocityY *= -1;

		positionX += velocityX;
		positionY += velocityY;

		DrawPixel(positionX, positionY, Cr);
	}

	//Dx���C�u�����I������
	DxLib_End();
	return 0;
}