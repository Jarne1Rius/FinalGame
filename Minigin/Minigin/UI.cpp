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
	for (auto& player :GameInstance::GetInstance().GetPlayers())
	{
		player.Render(m_TextRenderer, { 100,20 });
	}
}

void Rius::UI::Cleanup()
{
	delete m_TextRenderer;
}


Rius::UI::UI()
{
}
