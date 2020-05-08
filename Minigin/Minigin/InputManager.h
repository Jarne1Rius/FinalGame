#pragma once
#include <XInput.h>
#include "Singleton.h"
#include <map>
#include <thread>

#include "../SDL2/include/SDL.h"
#include "Command.h"

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
		RightStick,
		LeftStick,
		RightTrigger,
		LeftTrigger
	};
	//typedef std::map<KeyFunctions, std::pair<ControllerButton, SDL_Scancode>>  ControllerMap;
	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();
		bool ProcessInput();
		void ProcessInputt(GameObject* gameObject,int id);
		void Test(GameObject* gameObject);
		//void ChangeKey(KeyFunctions function, ControllerButton GamepadKeys);
		//void ChangeKey(KeyFunctions function, SDL_Scancode Keys);
		//ControllerMap GetControls() const { return m_Controles; }
		float IsPressed(ControllerButton button, int id) const;
		glm::vec2 GetAxisGamePad(KeyFunctions button, int id) const;
		float LeftStickY(int id) const;
		float LeftStickX(int id) const;
		float RightStickX(int id) const;
		float RightStickY(int id) const;
		float RightTrigger(int id) const;
		float LeftTrigger(int id) const;
		glm::vec2 LeftStick(int id) const;
		glm::vec2 RightStick(int id) const;
		void SetRumble(float left, float right) const;

	private:
		bool LStickInDeadZone(int id) const;
		bool RStickInDeadZone(int id) const;
		const static int m_Size{ 14 };
		std::vector <std::thread> m_Threads;
		std::vector<XINPUT_STATE> m_CurrentState{};
		int m_Id;
		bool m_Buttons[m_Size];
		Command* m_ButtonsCommand[m_Size];
		//ControllerMap m_Controles;
		const Uint8* m_Keyboard;
		std::vector<int> m_Controllers;
		bool m_Stop;

	};

}
