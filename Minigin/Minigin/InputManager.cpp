#include "MiniginPCH.h"
#include "InputManager.h"
#include <thread>


#include "GameInstance.h"
#include "Logger.h"
#include "UI.h"
Rius::InputManager::InputManager()
	:m_Id(1), m_CurrentState(), m_Controllers(), m_ButtonsCommand{}, m_Stop(), m_Buttons{},m_Pool(10)
{
	m_ButtonsCommand[int(ControllerButton::ButtonA)] = new JumpCommand{};
	m_ButtonsCommand[int(ControllerButton::ButtonB)] = new FireCommand{};
	m_ButtonsCommand[int(ControllerButton::LeftStick)] = new MoveLeft{};
	m_ButtonsCommand[int(ControllerButton::RightStick)] = new MoveRight{};
	m_ButtonsCommand[int(ControllerButton::ButtonY)] = new NewPlayerAdd{};
	for (int i = 0; i < m_Size; ++i)
	{
		if (m_ButtonsCommand[i] == nullptr)
			m_ButtonsCommand[i] = new Command();
	}
	for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		const DWORD dwResult = XInputGetState(i, &state);
		m_Connected[i] = (dwResult == ERROR_SUCCESS);
	}
}

Rius::InputManager::~InputManager()
{
	m_Stop = true;
	for (int i = 0; i < m_Size; ++i)
	{
		delete m_ButtonsCommand[i];
	}
}

void Rius::InputManager::ProcessInputt(GameObject* gameObject, int id, int playerid)
{
	m_ButtonsCommand[id]->Execute(gameObject, IsPressed(ControllerButton(id), playerid));
}

void Rius::InputManager::Test()
{
	UpdateGamepadState();
	for (int i = 0; i < GameInstance::GetInstance().AmountOfPlayers(); ++i)
	{
		if (GameInstance::GetInstance().GetPlayer(i).dead) continue;;
		//m_Pool.enqueue([this,i] {
			for (int a{}; a < m_Size; a++)
			{
				ProcessInputt(GameInstance::GetInstance().GetPlayer(i).pPlayer, a, GameInstance::GetInstance().GetPlayer(i).IdController);
			}
		//});
	}
}


float Rius::InputManager::IsPressed(ControllerButton button, int id) const
{
	if (button == ControllerButton::RightStick)
		return RightStickX(id);
	else if (button == ControllerButton::LeftStick)
		return LeftStickX(id);
	return float((m_CurrentState[id].Gamepad.wButtons & XINPUT_Buttons[int(button)]) ? 1 : 0);
}

void Rius::InputManager::ChangeCommand(ControllerButton button, Command* newCommand)
{
	delete m_ButtonsCommand[int(button)];
	m_ButtonsCommand[int(button)] = newCommand;

}

void Rius::InputManager::UpdateGamepadState()
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i)
	{
		if (!m_Connected[i])
			return;

		const DWORD dwResult = XInputGetState(i, &m_CurrentState[i]);
		m_Connected[i] = (dwResult == ERROR_SUCCESS);
	}
}

int Rius::InputManager::GetGamepadId()
{
	for (int k = 0; k < 4; ++k)
	{
		bool avail{ true };
		for (int i = 0; i < GameInstance::GetInstance().AmountOfPlayers(); ++i)
		{

			if (GameInstance::GetInstance().GetPlayer(i).IdController == k) avail = false;
		}
		if (m_Connected[k] && avail)
		{
			return k;
		}
	}
	Logger::LogError("NoNewGamePadConnected");
	return  -1;
}

glm::vec2 Rius::InputManager::GetAxisGamePad(KeyFunctions button, int id) const
{
	/*if (m_CurrentState.size() >= id)return { 0,0 };
	ControllerMap::const_iterator a = m_Controles.find(button);
	const std::pair<ControllerButton, SDL_Scancode> p = (*a).second;
	switch (p.first)
	{
	case ControllerButton::RightStick:
		return LeftStick(id);
		break;
	case ControllerButton::LeftStick:
		return LeftStick(id);
		break;
	default:
		return glm::vec2(0, 0);
		break;
	}*/
	return glm::vec2(0, 0);
}

float Rius::InputManager::LeftStickY(int id) const
{
	short x = m_CurrentState[id].Gamepad.sThumbLY;
	if (LStickInDeadZone(id)) return 0;
	return (static_cast<float>(x) / 32768.0f);
}

float Rius::InputManager::LeftStickX(int id) const
{
	short x = m_CurrentState[id].Gamepad.sThumbLX;
	if (LStickInDeadZone(id)) return 0;
	return (static_cast<float>(x) / 32768.0f);
}

float Rius::InputManager::RightStickX(int id) const
{
	short x = m_CurrentState[id].Gamepad.sThumbRX;
	if (RStickInDeadZone(id)) return 0;
	return (static_cast<float>(x) / 32768.0f);
}

float Rius::InputManager::RightStickY(int id) const
{
	short x = m_CurrentState[id].Gamepad.sThumbRY;
	if (RStickInDeadZone(id)) return 0;
	return (static_cast<float>(x) / 32768.0f);
}

float Rius::InputManager::RightTrigger(int id) const
{
	BYTE axis = m_CurrentState[id].Gamepad.bRightTrigger;

	if (axis > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		return axis / 255.0f;
	return 0.0f; // Trigger was not pressed
}

float Rius::InputManager::LeftTrigger(int id) const
{
	BYTE axis = m_CurrentState[id].Gamepad.bLeftTrigger;

	if (axis > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		return axis / 255.0f;
	return 0.0f; // Trigger was not pressed
}

glm::vec2 Rius::InputManager::LeftStick(int id) const
{
	return glm::vec2(LeftStickX(id), LeftStickY(id));
}

glm::vec2 Rius::InputManager::RightStick(int id) const
{
	return glm::vec2(RightStickX(id), RightStickY(id));
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

bool Rius::InputManager::LStickInDeadZone(int id) const
{
	short x = m_CurrentState[id].Gamepad.sThumbLX;
	short y = m_CurrentState[id].Gamepad.sThumbLY;
	if (x > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || x < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return false;
	if (y > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || y < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return false;
	return true;
}

bool Rius::InputManager::RStickInDeadZone(int id) const
{
	short x = m_CurrentState[id].Gamepad.sThumbRX;
	short y = m_CurrentState[id].Gamepad.sThumbRY;
	if (x > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE || x < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		return false;
	if (y > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE || y < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		return false;
	return true;
}

