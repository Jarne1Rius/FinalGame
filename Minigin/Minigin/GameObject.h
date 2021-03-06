#pragma once
#include "Transform.h"
#include "BaseComponent.h"
#include "Extra.h"
#include "Subject.h"
namespace Rius
{
	class PlayerComponent;
	class RigidBodyComponent;
	class Texture2D;
	class Subject;
	class GameObject : public Subject
	{
	public:
		virtual void Update(float deltaT);
		virtual void LateUpdate();
		virtual void Render() const;
		virtual void Initialize();
		virtual GameObject* Clone();
		//void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other);
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void AddComponent(BaseComponent* component);

		RigidBodyComponent* GetRigidBodyComponent() const { return m_pRigidBodyComponent; }
		void AddComponent(RigidBodyComponent* rigid);
		PlayerComponent* GetPlayerComponent() const { return m_pPlayerComponent; }
		void AddComponent(PlayerComponent* playerComponent);

		virtual void OnTriggerEnter(Collider* other);
		virtual void OnCollisionEnter(Collider* other);


		std::vector<GameObject*> GetAllChildren() const { return m_pChildren; }
		std::vector<BaseComponent*> GetAllComponents() const { return m_pComponents; }
		GameObject* GetParent() const { return  m_pParentObject; }
		Transform& GetTransform() { return m_Transform; }
		Tag GetTag()const { return m_Tag; }
		void SetTag(Tag tag) { m_Tag = tag; };
		bool GetStatic() const { return m_Static; }
		void SetStatic(bool isStatic) { m_Static = isStatic; }
		int GetId() const { return m_Id; }
		void SetActive(bool active = false) { m_Active = active; }
		bool GetActive()const { return m_Active; }
		
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
		void SetPreviousPos(const glm::vec3& pos) { m_PreviousPos = pos; };
		glm::vec3 getPreviousPos()const { return m_PreviousPos; };
		//Need to change this
	protected:
		RigidBodyComponent* m_pRigidBodyComponent;
	private:
		bool m_Static;
		bool m_Active = true;
		int m_Id;
		static int m_CurrentID;
		Tag m_Tag;
		glm::vec3 m_PreviousPos;

		class GameScene* m_pParentScene;
		GameObject* m_pParentObject;
		
		Transform m_Transform;
		PlayerComponent* m_pPlayerComponent;
		std::vector<BaseComponent*> m_pComponents;
		std::vector<GameObject*> m_pChildren;
	};
}
