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
	keys[KEY_INPUT_SPACE] = KeyState();
	keys[KEY_INPUT_BACK] = KeyState();
	keys[KEY_INPUT_1] = KeyState();
	keys[KEY_INPUT_2] = KeyState();
	keys[KEY_INPUT_3] = KeyState();
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
	Push = Press = Release = false;
}

void InputController::KeyState::InputUpdate(bool input)
{
	Push = (input && !Press);
	Release = (!input && Press);
	Press = input;
}

bool InputController::GetPush(int keyCode) const
{
	return keys.find(keyCode)->second.Push;
}

bool InputController::GetPress(int keyCode) const
{
	return keys.find(keyCode)->second.Press;
}

bool InputController::GetRelease(int keyCode) const
{
	return keys.find(keyCode)->second.Release;
}