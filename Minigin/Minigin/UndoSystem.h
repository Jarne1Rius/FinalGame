#pragma once
#include "BaseComponent.h"

namespace Rius
{
	struct Data
	{
		int gameObjectID;
		BaseComponent* pComponent;
		~Data()
		{
			delete pComponent;
		}
	};
	struct Node
	{
		Node* pNext;
		Node* pPrevious;
		Data* data;
		void Destroy()
		{
			delete data;
			if(pPrevious != nullptr)
			{
				pPrevious->Destroy();
				delete pPrevious;
			}
		}
		void DeleteData()
		{
			delete data;
		}
		void DeleteNext()
		{
			delete data;
			if(pNext != nullptr)
			{
				pNext->DeleteNext();
				delete pNext;
			}
		}
	};
	class UndoSystem
	{
	public:
		void AddAction(BaseComponent* component);
		void Undo();
		void Redo();
		void SetAmountRedu(int amount);
		~UndoSystem();
	private:
		Node* m_pHead = nullptr;
		Node* m_pLast = nullptr;
		int m_Size{};
		int m_MaxSize = 10;
	};
}

