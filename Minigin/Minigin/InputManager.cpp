#include "MiniginPCH.h"
#include "InputManager.h"
#include <thread>
Rius::InputManager::InputManager()
	:m_Id(1),m_CurrentState(),m_Controllers(),m_ButtonsCommand{},m_Stop(),m_Buttons{},m_Threads()
{
	m_ButtonsCommand[int(ControllerButton::ButtonA)] = new JumpCommand{};
	m_ButtonsCommand[int(ControllerButton::LeftStick)] = new MoveLeft{};
	m_ButtonsCommand[int(ControllerButton::RightStick)] = new MoveRight{};
	for (int i = 0; i < m_Size; ++i)
	{
		if (m_ButtonsCommand[i] == nullptr)
			m_ButtonsCommand[i] = new Command();
	}

	for (int i{ 0 }; i < XUSER_MAX_COUNT; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		// Simply get the state of the controller from XInput.
		DWORD dwResult = XInputGetState(i, &state);

		if (dwResult == ERROR_SUCCESS)
		{
			m_Id = i;
			for (int k = 0; k <int(m_Controllers.size()); k++)
			{
				if (k == i) i = -1;
			};  // Connected
			if (i != -1)
			{
				m_CurrentState.push_back(state);
				m_Controllers.push_back(i);
				//m_Threads.push_back(std::thread(&InputManager::ProcessInputt, this, m_Controllers[i]));
			}
		}
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

bool Rius::InputManager::ProcessInput()
{
	for (int i = 0; i <int( m_Controllers.size()); i++)
	{
		ZeroMemory(&m_CurrentState[i], sizeof(XINPUT_STATE));

		XInputGetState(m_Id, &m_CurrentState[i]);
	}


	return true;
}

void Rius::InputManager::ProcessInputt(GameObject* gameObject, int id)
{

	//while (m_Stop)
	{
		m_ButtonsCommand[id]->Execute(gameObject, IsPressed(ControllerButton(id), 0));
	}

}

void Rius::InputManager::Test(GameObject* gameObject)
{
	for (int a{}; a < m_Size; a++)
	{
		ProcessInputt(gameObject, a);
		/*if(IsPressed(ControllerButton(a)) && !m_Buttons[a]->m_Pressed)
			m_Buttons[a]->Execute(actor);
		m_Buttons[a]->m_Pressed = IsPressed(ControllerButton(a));*/
	}
	//ProcessInputt(0);
	//std::thread threads[m_Size];
	//for (int a{}; a < m_Size; a++)
	//{
	//	
	//	threads[a] = std::thread{ &InputManager::ProcessInputt, this, gameObject,m_Id };
	//	//m_Threads.push_back(std::thread(&InputManager::ProcessInputt, this, m_Controllers[i]));
	//	//m_ButtonsCommand[a]->Execute(gameObject, IsPressed(ControllerButton(a), 0));
	//}
	//for (int i = 0; i < m_Size; ++i)
	//{
	//	threads[i].join();
	//}
}


float Rius::InputManager::IsPressed(ControllerButton button, int id) const
{
	if (button == ControllerButton::RightStick)
		return RightStickX(id);
	else if (button == ControllerButton::LeftStick)
		return LeftStickX(id);
	return float((m_CurrentState[id].Gamepad.wButtons & XINPUT_Buttons[int(button)])? 1:0);
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

