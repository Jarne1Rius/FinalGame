#include "MiniginPCH.h"
#include "InputManager.h"

Rius::InputManager::InputManager()
	:m_Id(1)
{
	
	for (int i{0}; i < int(KeyFunctions::Shoot); i++)
	{
		std::pair<KeyFunctions, std::pair<ControllerButton, SDL_Scancode>> pair(KeyFunctions(i), std::pair<ControllerButton, SDL_Scancode>(ControllerButton::ButtonA, SDL_SCANCODE_0));
		m_Controles.insert(pair);
	}
	for (int i{0}; i < 5; i++)
	{
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));

		DWORD result = XInputGetState(i, &m_CurrentState);

		if (result == ERROR_SUCCESS)
		{
			m_Id = i;
			break;  // Connected
		}
	}
	
}

bool Rius::InputManager::ProcessInput()
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_Id, &m_CurrentState);

	m_Keyboard = SDL_GetKeyboardState(NULL);
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
	}

	return true;
}

void Rius::InputManager::ChangeKey(KeyFunctions function, ControllerButton GamepadKeys) 
{
	ControllerMap::const_iterator a = m_Controles.find(function);
	const SDL_Scancode type = (*a).second.second;
	std::pair<ControllerButton, SDL_Scancode> KeyBinding(std::pair<ControllerButton, SDL_Scancode>(GamepadKeys,type));
	m_Controles.at(function) = KeyBinding;
}

void Rius::InputManager::ChangeKey(KeyFunctions function, SDL_Scancode Keys)
{
	ControllerMap::const_iterator a = m_Controles.find(function);
	const ControllerButton type = (*a).second.first;
	std::pair<KeyFunctions, std::pair<ControllerButton, SDL_Scancode>> KeyBinding(function, std::pair<ControllerButton, SDL_Scancode>(type, Keys));
	m_Controles.insert(KeyBinding);
}


float Rius::InputManager::IsPressed(KeyFunctions button) const
{
	ControllerMap::const_iterator a = m_Controles.find(button);
	std::pair<ControllerButton, SDL_Scancode> p = (*a).second;
	switch (p.first)
	{
	case ControllerButton::LeftTrigger:
		return LeftTrigger();
		break;
	case ControllerButton::RightTrigger:
		return RightTrigger();
		break;
	}
	return (m_CurrentState.Gamepad.wButtons& XINPUT_Buttons[int(p.first)]  || m_Keyboard[p.second]);
}

glm::vec2 Rius::InputManager::GetAxisGamePad(KeyFunctions button) const
{
	ControllerMap::const_iterator a = m_Controles.find(button);
	const std::pair<ControllerButton, SDL_Scancode> p = (*a).second;
	switch (p.first)
	{
	case ControllerButton::RightStick:
		return LeftStick();
		break;
	case ControllerButton::LeftStick:
		return LeftStick();
		break;
	default:
		return glm::vec2(0, 0);
		break;
	}
}

float Rius::InputManager::LeftStickY() const
{
	short x = m_CurrentState.Gamepad.sThumbLY;
	if (LStickInDeadZone()) return 0;
	return (static_cast<float>(x) / 32768.0f);
}

float Rius::InputManager::LeftStickX() const
{
	short x = m_CurrentState.Gamepad.sThumbLX;
	if (LStickInDeadZone()) return 0;
	return (static_cast<float>(x) / 32768.0f);
}

float Rius::InputManager::RightStickX() const
{
	short x = m_CurrentState.Gamepad.sThumbRX;
	if (RStickInDeadZone()) return 0;
	return (static_cast<float>(x) / 32768.0f);
}

float Rius::InputManager::RightStickY() const
{
	short x = m_CurrentState.Gamepad.sThumbRY;
	if (RStickInDeadZone()) return 0;
	return (static_cast<float>(x) / 32768.0f);
}

float Rius::InputManager::RightTrigger() const
{
	BYTE axis = m_CurrentState.Gamepad.bRightTrigger;

	if (axis > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		return axis / 255.0f;
	return 0.0f; // Trigger was not pressed
}

float Rius::InputManager::LeftTrigger() const
{
	BYTE axis = m_CurrentState.Gamepad.bLeftTrigger;

	if (axis > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		return axis / 255.0f;
	return 0.0f; // Trigger was not pressed
}

glm::vec2 Rius::InputManager::LeftStick() const
{
	//return glm::vec2();
	return glm::vec2(LeftStickX(), LeftStickY());
}

glm::vec2 Rius::InputManager::RightStick() const
{
	//return glm::vec2();
	return glm::vec2(RightStickX(), RightStickY());
}

void Rius::InputManager::SetRumble(float left, float right) const
{
	XINPUT_VIBRATION rumble;

	// Zero memory on vibration state
	ZeroMemory(&rumble, sizeof(XINPUT_VIBRATION));

	// Calculate vibration intensity
	int left_motor = int(left * 65535.0f);
	int right_motor = int(right * 65535.0f);

	rumble.wLeftMotorSpeed = left_motor;
	rumble.wRightMotorSpeed = right_motor;

	// Apply vibration
	XInputSetState(m_Id, &rumble);
}

bool Rius::InputManager::LStickInDeadZone() const
{
	short x = m_CurrentState.Gamepad.sThumbLX;
	short y = m_CurrentState.Gamepad.sThumbLY;
	if (x > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || x < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return false;
	if (y > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || y < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return false;
	return true;
}

bool Rius::InputManager::RStickInDeadZone() const
{
	short x = m_CurrentState.Gamepad.sThumbRX;
	short y = m_CurrentState.Gamepad.sThumbRY;
	if (x > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE || x < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		return false;
	if (y > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE || y < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		return false;
	return true;
}

