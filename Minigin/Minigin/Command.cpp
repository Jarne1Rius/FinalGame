#include "MiniginPCH.h"
#include "Command.h"

#include "GameInstance.h"
#include "GameObject.h"
#include "PlayerComponent.h"
void Rius::JumpCommand::Execute(GameObject* actor, float hit)
{
	//std::cout << "Jump";

	PlayerComponent* playerComp = actor->GetPlayerComponent();
	if (playerComp == nullptr) return;
	switch (m_Type)
	{
	case pressed:
		if (!m_Pressed && hit == 1)playerComp->Jump(hit);
		break;
	case release:
		if (m_Pressed && hit == 0)playerComp->Jump(hit);
		break;
	case hold:
		if (m_Pressed && hit == 1)playerComp->Jump(hit);
		break;
	}
	m_Pressed = (hit == 1);
}

void Rius::FireCommand::Execute(GameObject* actor, float hit)
{
	PlayerComponent* playerComp = actor->GetPlayerComponent();
	if (playerComp == nullptr) return;
	switch (m_Type)
	{
	case pressed:
		if (!m_Pressed && hit == 1)playerComp->Fire(hit);
		break;
	case release:
		if (m_Pressed && hit == 0)playerComp->Fire(hit);
		break;
	case hold:
		if (m_Pressed && hit == 1)playerComp->Fire(hit);
		break;
	}
	m_Pressed = (hit == 1);
}


void Rius::Move::Execute(GameObject* actor, float hit)
{
	if (actor->GetPlayerComponent() == nullptr && !actor->GetActive()) return;
	actor->GetPlayerComponent()->Move(hit);

}

void Rius::NewPlayerAdd::Execute(GameObject* actor, float hit)
{
	switch (m_Type)
	{
	case pressed:
		if (!m_Pressed && hit == 1)GameInstance::GetInstance().SetPos(actor);
		break;
	case release:
		if (m_Pressed && hit == 0)GameInstance::GetInstance().SetPos(actor);
		break;
	case hold:
		if (m_Pressed && hit == 1)GameInstance::GetInstance().SetPos(actor);
		break;
	}
	m_Pressed = (hit == 1);

}
