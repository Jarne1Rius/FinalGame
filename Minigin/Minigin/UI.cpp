#include "MiniginPCH.h"
#include "UI.h"
#include "GameObject.h"
#include "MaterialManager.h"
#include "Minigin.h"
#include "TextMaterial.h"
#include "HealthComponent.h"
#include "TextRenderer.h"
#include "InputManager.h"
Rius::Player::Player()
	:IdController(InputManager::GetInstance().GetGamepadId())
{
}

void Rius::Player::Render(TextRenderer* textRenderer, glm::vec2 pos) const
{
	//pos.y = float(Minigin::m_Height) ;
	//textRenderer->RenderText(pos, std::to_string(score), 1, m_color);
	//pPlayer->Render();
}

void Rius::Player::RemoveHealth()
{
	m_Health->RemoveHealth();
}

void Rius::UI::Initialize()
{
	TextMaterial* mat = new TextMaterial{"text",{0,1,1}};
	MaterialManager::AddMaterial(mat);
	m_TextRenderer = new TextRenderer{ {0,0},mat,"" };
}

void Rius::UI::Update()
{
	
}

void Rius::UI::AddPlayer(const Player& player)
{
	m_Players.push_back(player);
}

void Rius::UI::Render()
{
	for (Player player : m_Players)
	{
		player.Render(m_TextRenderer, { 100,20 });
	}
}

void Rius::UI::Cleanup()
{
	delete m_TextRenderer;
}

Rius::Player& Rius::UI::GetPlayer(int playerId)
{
	return m_Players[playerId];
}

Rius::Player& Rius::UI::GetPlayer(const GameObject* player)
{
	for (Player& p : m_Players)
	{
		if (p.pPlayer == player)
		{
			return p;
		}
	}
	return m_Players[0];
}

Rius::UI::UI()
{
}
