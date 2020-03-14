#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "BaseComponent.h"
#include "Tags.h"
namespace Rius
{
	class Texture2D;
	class GameObject : public SceneObject
	{
	public:
		void Update() override;
		void Render() const override;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		std::vector<GameObject*> GetAllChildren() const { return m_pChildren; }
		std::vector<BaseComponent*> GetAllComponents() const { return m_pComponents; }
		GameObject* GetParent() const { return  m_pParentObject; }
		Transform GetTransform() const { return m_Transform; }
		Tag GetTag()const { return m_Tag; }
		void SetTag(Tag tag) { m_Tag = tag; };
		bool GetStatic() { return m_Static; }
		
		template <typename T>
		T* GetComponent()
		{
			const type_info& ti = typeid(T);
			for (auto* component : m_pComponents)
				if (component && typeid(*component) == ti) return component;
			return nullptr;
		}
		template <typename T>
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
	private:
		Transform m_Transform;
		std::shared_ptr<Texture2D> m_Texture{};
		std::vector<BaseComponent*> m_pComponents{};
		std::vector<GameObject*> m_pChildren{};
		Tag m_Tag{};
		bool m_Static;
		
		class GameScene* m_pParentScene;
		GameObject* m_pParentObject;

	};
}
