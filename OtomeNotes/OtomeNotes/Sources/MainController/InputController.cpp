#include"DxLib.h"
#include<unordered_map>
#include"InputController.h"

InputController& InputController::getInstance()
{
	static InputController instance;
	return instance;
}

void InputController::Init()
{
	keys[KEY_INPUT_Z] = KeyState();
}

void InputController::InputUpdate()
{
	char Buf[256];

	GetHitKeyStateAll(Buf);

	for(auto&& var : keys)
	{
		var.second.InputUpdate(Buf[var.first]);
	}
}

InputController::KeyState::KeyState()
{
	Push = Press = false;
}

void InputController::KeyState::InputUpdate(bool input)
{
	if (input)
	{
		if (Press)
		{
			Push = false;
		}
		else
		{
			Push = true;
			Press = true;
		}
	}
	else
	{
		Push = false;
		Press = false;
	}
}

bool InputController::GetPush(int keyCode) const
{
	return keys.find(keyCode)->second.Push;
}

bool InputController::GetPress(int keyCode) const
{
	return keys.find(keyCode)->second.Press;
}