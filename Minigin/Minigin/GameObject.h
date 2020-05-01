#pragma once
#include "Transform.h"
#include "BaseComponent.h"
#include "Extra.h"
#include "RigidBodyComponent.h"

namespace Rius
{
	class Texture2D;
	class GameObject final
	{
	public:
		void Update();
		void LateUpdate();
		void Render() const;
		void Initialize();

		//void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void AddComponent(BaseComponent* component);
		
		RigidBodyComponent* GetRigidBodyComponent() { return m_pRigidBodyComponent; }
		void AddComponent(RigidBodyComponent* rigid);
		//getters
		std::vector<GameObject*> GetAllChildren() const { return m_pChildren; }
		std::vector<BaseComponent*> GetAllComponents() const { return m_pComponents; }
		GameObject* GetParent() const { return  m_pParentObject; }
		Transform& GetTransform() { return m_Transform; }
		Tag GetTag()const { return m_Tag; }
		void SetTag(Tag tag) { m_Tag = tag; };
		bool GetStatic() const { return m_Static; }
		void SetStatic(bool isStatic) { m_Static = isStatic; }
		int GetId() { return m_Id; }
		BaseComponent* GetComponentById(int id);
		template <class  T>
		T* GetComponent()
		{
			const type_info& ti = typeid(T);
			for (auto* component : m_pComponents)
				if (component && typeid(*component) == ti) return static_cast<T*>(component);
			return nullptr;
		}
		template <class T >
		T* GetChild()
		{
			const type_info& ti = typeid(T);
			for (auto* child : m_pChildren)
				if (child && typeid(child) == ti) return child;
			return nullptr;
		}
		template<typename T>
		std::vector<T*> GetChildren()
		{
			const type_info& ti = typeid(T);
			std::vector<T*> pChildren(m_pChildren.size());

			for (auto* child : m_pChildren)
			{
				if (child && typeid(child) == ti)
					pChildren.push_back(pChildren);
			}
			return  nullptr;
		}
		glm::vec3 m_PreviousPos;
	private:
		Transform m_Transform;
		RigidBodyComponent* m_pRigidBodyComponent;
		std::vector<BaseComponent*> m_pComponents{};
		std::vector<GameObject*> m_pChildren{};
		Tag m_Tag{};
		bool m_Static;
		int m_Id;
		class GameScene* m_pParentScene;
		GameObject* m_pParentObject;
	
		static int m_CurrentID;
	};
}
