#include "MiniginPCH.h"
#include "UI.h"

#include "GameInstance.h"
#include "GameObject.h"
#include "MaterialManager.h"
#include "Minigin.h"
#include "TextMaterial.h"
#include "HealthComponent.h"
#include "TextRenderer.h"
#include "InputManager.h"


void Rius::UI::Initialize()
{
	TextMaterial* mat = new TextMaterial{ "text",{0,1,1} };
	MaterialManager::AddMaterial(mat);
	m_TextRenderer = new TextRenderer{ {0,0},mat,"" };
}

void Rius::UI::Update()
{

}

void Rius::UI::Render()
{
	glm::vec2 pos{ 0,20 };
	std::string name{ "Player1" };
	for (auto& player : GameInstance::GetInstance().GetPlayers())
	{
		if (player.pPlayer->GetActive())
		{
			player.Render(m_TextRenderer, pos, name);
			pos.x = float(Minigin::m_Width) - 100;
			name = "Player2";
		}
	}
}

void Rius::UI::Cleanup()
{
	delete m_TextRenderer;
}