#include "MiniginPCH.h"
#include "UndoSystem.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include  "RigidBodyComponent.h"
void Rius::UndoSystem::AddAction(BaseComponent* component)
{
	if (m_MaxSize <= m_Size)
	{
		//create new node
		Data* data = new Data{};
		data->gameObjectID = component->GetGameObject()->GetId();
		data->pComponent = component->Clone();
		data->pComponent->setID(component->GetId());
		Node* pNewNode = new Node{ nullptr,nullptr,data };

		//Set Last Node;
		Node* last = m_pLast;
		m_pLast = last->pNext;
		m_pLast->pPrevious = nullptr;
		last->DeleteData();
		delete last;

		pNewNode->pPrevious = m_pHead;
		m_pHead->pNext = pNewNode;
		m_pHead = pNewNode;
		m_Size = m_MaxSize;
	}
	else
	{

		//create new node
		Data* data = new Data{};
		data->gameObjectID = component->GetGameObject()->GetId();
		data->pComponent = component->Clone();
		data->pComponent->setID(component->GetId());
		Node* pNewNode = new Node{ nullptr,nullptr,data };

		//check if item in list
		if (m_pHead != nullptr)
		{
			m_pHead->pNext = pNewNode;
			pNewNode->pPrevious = m_pHead;
		}
		else
		{
			m_pLast = pNewNode;
		}

		m_pHead = pNewNode;
		if (m_pHead->pNext != nullptr)
		{
			m_pHead->pNext->DeleteNext();
			m_pHead->pNext = nullptr;
		}
		m_Size++;
	}
}

void Rius::UndoSystem::Undo()
{
	if (m_pHead == nullptr) return;
	GameObject* undoGame = nullptr;
	for (GameObject* gameObject : SceneManager::GetCurrentScene()->m_pObjects)
	{
		if (gameObject->GetId() == m_pHead->data->gameObjectID)
		{
			undoGame = gameObject;
			break;
		}
	}
	if (undoGame == nullptr) return;

	//replace component
	BaseComponent* comp = undoGame->GetComponentById(m_pHead->data->pComponent->GetId());
	comp->SetComponent(m_pHead->data->pComponent);

	//ini new head + set head previous to previous head
	Node* previous = m_pHead->pPrevious;
	if (previous != nullptr)
	{
		m_pHead = previous;
		m_Size--;
	}
}

void Rius::UndoSystem::Redo()
{
	if (m_pHead->pNext == nullptr) return;
	GameObject* undoGame = nullptr;
	for (GameObject* gameObject : SceneManager::GetCurrentScene()->m_pObjects)
	{
		if (gameObject->GetId() == m_pHead->pNext->data->gameObjectID)
		{
			undoGame = gameObject;
			break;
		}
	}
	if (undoGame == nullptr) return;
	//replace component
	BaseComponent* comp = undoGame->GetComponentById(m_pHead->pNext->data->pComponent->GetId());
	comp->SetComponent(m_pHead->data->pComponent);
	m_pHead = m_pHead->pNext;
	m_Size++;
}

void Rius::UndoSystem::SetAmountRedu(int amount)
{
	m_MaxSize = amount;
	if (m_pHead != nullptr)
	{
		m_pLast = nullptr;
		m_pHead->Destroy();
		delete m_pHead;
	}
}

Rius::UndoSystem::~UndoSystem()
{
	if (m_pHead != nullptr)
	{
		m_pLast = nullptr;
		m_pHead->Destroy();
		delete m_pHead;
	}

}
