#include "MiniginPCH.h"
#include "InputManager.h"

Rius::InputManager::InputManager()
	:m_id(1)
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
			m_id = i;
			break;  // Connected
		}
	}
	
}

bool Rius::InputManager::ProcessInput()
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_id, &m_CurrentState);

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
	std::pair<KeyFunctions, std::pair<ControllerButton, SDL_Scancode>> KeyBinding(function, std::pair<ControllerButton, SDL_Scancode>(GamepadKeys,type));
	m_Controles.insert(KeyBinding);
}

void Rius::InputManager::ChangeKey(KeyFunctions function, SDL_Scancode Keys)
{
	ControllerMap::const_iterator a = m_Controles.find(function);
	const ControllerButton type = (*a).second.first;
	std::pair<KeyFunctions, std::pair<ControllerButton, SDL_Scancode>> KeyBinding(function, std::pair<ControllerButton, SDL_Scancode>(type, Keys));
	m_Controles.insert(KeyBinding);
}


bool Rius::InputManager::IsPressed(KeyFunctions button) const
{
	ControllerMap::const_iterator a = m_Controles.find(button);
	std::pair<ControllerButton, SDL_Scancode> p = (*a).second;
	return (m_CurrentState.Gamepad.wButtons& XINPUT_Buttons[int(p.first)]  || m_Keyboard[p.second]);
}

