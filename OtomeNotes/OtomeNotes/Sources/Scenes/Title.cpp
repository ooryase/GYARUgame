#include"DxLib.h"
#include"Title.h"

Title::Title() : VirtualScene()
{

}

void Title::Update()
{

}

void Title::Draw() const
{
	DrawString(200,200,"TITLE",GetColor(0,0,0),GetColor(255,255,255));
}