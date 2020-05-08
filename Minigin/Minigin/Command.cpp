#include "MiniginPCH.h"
#include "Command.h"
#include "GameObject.h"
#include "PlayerComponent.h"
void Rius::JumpCommand::Execute(const GameObject* actor, float hit)
{
	//std::cout << "Jump";

	if (actor->GetPlayerComponent() == nullptr) return;
	switch (m_Type)
	{
	case pressed:
		if (!m_Pressed && (hit == 1))actor->GetPlayerComponent()->Jump(hit);
			break;
	case release:
		if (m_Pressed && (hit == 0))actor->GetPlayerComponent()->Jump(hit);
		break;
	case hold:
		if (m_Pressed && (hit == 1))actor->GetPlayerComponent()->Jump(hit);
		break;
	}
	m_Pressed = (hit == 1);
}

void Rius::FireCommand::Execute(const GameObject* actor, float hit)
{
}

void Rius::MoveLeft::Execute(const GameObject* actor, float hit)
{
	if (actor->GetPlayerComponent() == nullptr) return;
	actor->GetPlayerComponent()->Move(hit);
	//switch (m_Type)
	//{
	//case pressed:
	//	if (!m_Pressed && (hit == 1))
	//	break;
	//case release:
	//	if (m_Pressed && (hit == 0))actor->GetRigidBodyComponent()->AddForce(force);
	//	break;
	//case hold:
	//	if (m_Pressed && (hit == 1))actor->GetRigidBodyComponent()->AddForce(force);
	//	break;
	//}
	//m_Pressed = (hit==1);
}

void Rius::MoveRight::Execute(const GameObject* actor, float hit)
{
	if (actor->GetPlayerComponent() == nullptr) return;
	actor->GetPlayerComponent()->Move(hit);
	//glm::vec2 force{ 1,0 };
	//switch (m_Type)
	//{
	//case pressed:
	//	if (!m_Pressed && (hit == 1))actor->GetRigidBodyComponent()->AddForce(force);
	//	break;
	//case release:
	//	if (m_Pressed && (hit == 0))actor->GetRigidBodyComponent()->AddForce(force);
	//	break;
	//case hold:
	//	if (m_Pressed && (hit == 1))actor->GetRigidBodyComponent()->AddForce(force);
	//	break;
	//}
	//m_Pressed = (hit == 1);
}
