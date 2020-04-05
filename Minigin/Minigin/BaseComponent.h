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

		class GameObject* GetGameObject() const { return m_pGameObject; };
		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Render() const = 0;
		virtual void OnTriggerEnter(Collider* collider);
		virtual void OnTriggerStay(Collider* collider);
		virtual void OnCollisionEnter(Collider* collider);
		virtual void OnTriggerExit(Collider* collider);
		virtual void OnCollisionStay(Collider* collider);
		virtual void OnCollisionExit(Collider* collider);

	protected:
		class GameObject* m_pGameObject;
	};

}

