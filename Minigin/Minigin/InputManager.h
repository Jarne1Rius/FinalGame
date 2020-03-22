#pragma once
#include <XInput.h>
#include "Singleton.h"
#include <map>
#include "../SDL2/include/SDL.h"

#include "Extra.h"


namespace Rius
{
	static const WORD XINPUT_Buttons[] = {
	XINPUT_GAMEPAD_A,
	XINPUT_GAMEPAD_B,
	XINPUT_GAMEPAD_X,
	XINPUT_GAMEPAD_Y,
	XINPUT_GAMEPAD_DPAD_UP,
	XINPUT_GAMEPAD_DPAD_DOWN,
	XINPUT_GAMEPAD_DPAD_LEFT,
	XINPUT_GAMEPAD_DPAD_RIGHT,
	XINPUT_GAMEPAD_LEFT_SHOULDER,
	XINPUT_GAMEPAD_RIGHT_SHOULDER,
	XINPUT_GAMEPAD_LEFT_THUMB,
	XINPUT_GAMEPAD_RIGHT_THUMB,
	XINPUT_GAMEPAD_START,
	XINPUT_GAMEPAD_BACK,
	};
	enum class ControllerButton
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY,
		DPadUp,
		DPadDown,
		DPadRight,
		DPadLeft,
		LeftShoulder,
		RightShoulder,
		LeftThumb,
		RightThumb,
	};
	typedef std::map<KeyFunctions, std::pair<ControllerButton, SDL_Scancode>>  ControllerMap;
	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		bool ProcessInput();
		void ChangeKey(KeyFunctions function, ControllerButton GamepadKeys);
		void ChangeKey(KeyFunctions function, SDL_Scancode Keys);
		std::map<std::string, ControllerButton> GetControls() const;
		bool IsPressed(KeyFunctions button) const;
	private:
		const static int m_Size{14};
		XINPUT_STATE m_CurrentState{};
		int m_id;
		bool m_Buttons[m_Size];
		ControllerMap m_Controles;
		const Uint8* m_Keyboard;
	};

}
