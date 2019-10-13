#include<iostream>
#include<unordered_map>
#include"DxLib.h"

////Singleton
class InputController
{
private:
	InputController() {}
	InputController(const InputController&) = delete;
	InputController& operator = (const InputController&) = delete;

	class KeyState
	{
	public:
		bool Push;
		bool Press;

		KeyState();

		void InputUpdate(bool input);
	};

	std::unordered_map<int, KeyState> keys;
public:
	static InputController& getInstance();

	void Init();
	void InputUpdate();

	bool GetPush(int keyCode) const;
	bool GetPress(int keyCode) const;
	

	/*public static void InputUpdate()
	{
		keyboardState = Keyboard.GetState();

		foreach(var k in keyStates)
		{
			k.Value.InputUpdate(k.Key);
		}

		lastGamePadState = currentGamePadState;
		currentGamePadState = GamePad.GetState(PlayerIndex.One);
	}

	public static bool IsPush(Keys keys)
	{
		return keyStates[keys].push;
	}

	public static bool IsPress(Keys keys)
	{
		return keyStates[keys].press;
	}

	public static bool IsPress(Buttons buttons)
	{
		switch (buttons)
		{
		case Buttons.A:
			return currentGamePadState.Buttons.A == ButtonState.Pressed;
		case Buttons.B:
			return currentGamePadState.Buttons.B == ButtonState.Pressed;

		default:
			return false;

		}
	}

	public static bool IsPush(Buttons buttons)
	{
		switch (buttons)
		{
		case Buttons.A:
			return (currentGamePadState.Buttons.A == ButtonState.Pressed &&
				lastGamePadState.Buttons.A == ButtonState.Released);
		case Buttons.B:
			return (currentGamePadState.Buttons.B == ButtonState.Pressed &&
				lastGamePadState.Buttons.B == ButtonState.Released);
		default:
			return false;

		}
	}

	public static float StickLeftX()
	{
		return currentGamePadState.ThumbSticks.Left.X;
	}
	public static float StickLeftY()
	{
		return currentGamePadState.ThumbSticks.Left.Y;
	}
	public static float StickRightX()
	{
		return currentGamePadState.ThumbSticks.Right.X;
	}
	public static float StickRightY()
	{
		return currentGamePadState.ThumbSticks.Right.Y;
	}*/
};