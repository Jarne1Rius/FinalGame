#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "TextMaterial.h"
#include "MaterialManager.h"
#include "Minigin.h"
#include "Time.h"

Rius::FpsComponent::FpsComponent(glm::vec3 color, const std::string& font)
{
	m_pMat = new TextMaterial{"FPS",color};
	MaterialManager::AddMaterial(m_pMat);
	m_pTextRenderer = new TextRenderer{ {0, Minigin::m_Height},m_pMat,"",font};
}

Rius::FpsComponent::~FpsComponent()
{
	delete m_pTextRenderer;
}


void Rius::FpsComponent::Initialize()
{

}

void Rius::FpsComponent::Render() const
{
	m_pTextRenderer->ChangeText(std::to_string(Time::m_CurrentFrames));
	m_pTextRenderer->Render();
}

void Rius::FpsComponent::SetComponent(BaseComponent* )
{
}

Rius::BaseComponent* Rius::FpsComponent::Clone()
{
	return nullptr;
}
