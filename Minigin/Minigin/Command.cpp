#include "MiniginPCH.h"
#include "Command.h"

#include "GameInstance.h"
#include "GameObject.h"
#include "PlayerComponent.h"
void Rius::JumpCommand::Execute( GameObject* actor, float hit)
{
	//std::cout << "Jump";

	if (actor->GetPlayerComponent() == nullptr) return; 
	switch (m_Type)
	{
	case pressed:
		//std::cout << "test\n";
		if (!m_Pressed && (hit == 1))actor->GetPlayerComponent()->Jump(hit);
			break;
	case release:
		//std::cout << "test\n";
		if (m_Pressed && (hit == 0))actor->GetPlayerComponent()->Jump(hit);
		break;
	case hold:
		//std::cout << "test\n";
		if (m_Pressed && (hit == 1))actor->GetPlayerComponent()->Jump(hit);
		break;
	}
	m_Pressed = (hit == 1);
}

void Rius::FireCommand::Execute( GameObject* actor, float hit)
{
	if (actor->GetPlayerComponent() == nullptr) return;
	//if (hit == 1) std::cout << "ahah";
	switch (m_Type)
	{
	case pressed:
		//std::cout << "test\n";
		if (!m_Pressed && (hit == 1))actor->GetPlayerComponent()->Fire(hit);
		break;
	case release:
		//std::cout << "test\n";
		if (m_Pressed && (hit == 0))actor->GetPlayerComponent()->Fire(hit);
		break;
	case hold:
		//std::cout << "test\n";
		if (m_Pressed && (hit == 1))actor->GetPlayerComponent()->Fire(hit);
		break;
	}
	m_Pressed = (hit == 1);
}

void Rius::MoveLeft::Execute( GameObject* actor, float hit)
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

void Rius::MoveRight::Execute( GameObject* actor, float hit)
{
	if (actor->GetPlayerComponent() == nullptr && !actor->GetActive()) return;
//	if(!GameInstance::GetInstance().Alive(actor)) return;
//	std::cout << GameInstance::GetInstance().Alive(actor) << "\n";
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

void Rius::NewPlayerAdd::Execute(GameObject* actor, float hit)
{
	if(hit == 1)
		GameInstance::GetInstance().SetPos(actor);
}
