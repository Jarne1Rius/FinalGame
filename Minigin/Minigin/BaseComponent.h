#pragma once

namespace Rius
{
	class Collider;
	class BaseComponent
	{
		friend class GameObject;
	public:
		BaseComponent();
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = default;
		BaseComponent(BaseComponent&& other) noexcept = default;
		BaseComponent& operator= (const BaseComponent& other) = default;
		BaseComponent& operator= (BaseComponent&& other) = default;
		virtual void SetComponent(BaseComponent* comp);
		class GameObject* GetGameObject() const { return m_pGameObject; };
		virtual void Initialize() = 0;
		virtual void Update(float deltaT) = 0;
		virtual void Render() const = 0;
		virtual void LateUpdate(){};
		virtual void OnTriggerEnter(Collider*){}
		virtual void OnTriggerStay(Collider*){}
		virtual void OnCollisionEnter(Collider*){}
		virtual void OnTriggerExit(Collider*){}
		virtual void OnCollisionStay(Collider*){}
		virtual void OnCollisionExit(Collider*){}
		virtual BaseComponent* Clone();
		int GetId() { return m_Id; }
		void setID(int id) { m_Id = id; }
	protected:
		int m_Id;
		class GameObject* m_pGameObject;
		static int m_CurrentID;
	};

}

