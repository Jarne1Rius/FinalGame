#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "TextMaterial.h"
#include "MaterialManager.h"
#include "Minigin.h"
#include "Time.h"

Rius::FPSComponent::FPSComponent(glm::vec3 color, const std::string& font)
{
	m_pMat = new TextMaterial{"FPS",color};
	MaterialManager::AddMaterial(m_pMat);
	m_pTextRenderer = new TextRenderer{ {0, Minigin::m_Height},m_pMat,"test",font};
}

Rius::FPSComponent::~FPSComponent()
{
	delete m_pTextRenderer;
}

void Rius::FPSComponent::Update(float deltaT)
{
	
}

void Rius::FPSComponent::Initialize()
{

}

void Rius::FPSComponent::Render() const
{
	m_pTextRenderer->ChangeText(std::to_string(Time::m_CurrentFrames));
	m_pTextRenderer->Render();
}

void Rius::FPSComponent::SetComponent(BaseComponent* comp)
{
}

Rius::BaseComponent* Rius::FPSComponent::Clone()
{
	return nullptr;
}
