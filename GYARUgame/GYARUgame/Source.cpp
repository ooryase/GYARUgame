#include"DxLib.h"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR IpCmdLine,
	_In_ int nCmdShow)
{
	ChangeWindowMode(TRUE);

	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	const unsigned int width = 640;
	const unsigned int height = 480;


	SetGraphMode(width, height, 32);

	SetWindowSizeExtendRate(1, 0);

	SetBackgroundColor(0x00, 0x00, 0x00);

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	unsigned int Cr = GetColor(255, 255, 255);

	//DrawLine(0, 0, 640, 480, Cr);

	//int dicColor = -1;
	int red = 255;

	//DrawBoxAA(200.f, 200.0f, 240.0f, 350.0f, Cr2, FALSE);

	float X = 300.0f;
	float Y = 300.0f;

	float dicX = 1.0f;
	float dicY = 1.0f;

	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//ClearDrawScreen();
		//SetDrawScreen(DX_SCREEN_FRONT);

		DrawBoxAA(30.0f, 30.0f, width - 30.0f, height - 30.0f, Cr, FALSE);

		X += dicX * 0.3f;
		Y += dicY * 0.3f;

		if (X > width - 30)
		{
			X = width - 30;
			dicX = -1.0f;
		}
		else if (X < 30)
		{
			X = 30;
			dicX = 1.0f;
		}

		if (Y > height - 30)
		{
			Y = height - 30;
			dicY = -1.0f;
		}
		else if (Y < 30)
		{
			Y = 30;
			dicY = 1.0f;
		}


		DrawPixel(X, Y, Cr);

		//red += dicColor * sankaku1.Update(width, height, 30.0f);
		//red += dicColor * sankaku2.Update(width, height, 30.0f);
		//red += dicColor * sankaku3.Update(width, height, 30.0f);

		//dicColor = (red >= 250) ? -1 : dicColor;
		//dicColor = (red <= 10) ? 1 : dicColor;

		//unsigned int Cr2 = GetColor(red, 0, 0);

		/*DrawTriangleAA(sankaku1.X, sankaku1.Y,
			sankaku2.X, sankaku2.Y,
			sankaku3.X, sankaku3.Y,
			Cr2, TRUE);*/

			//ScreenFlip();
	}

	//WaitKey();

	DxLib_End();

	return 0;
}
