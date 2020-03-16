#pragma once

namespace Rius
{
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

	protected:
		class GameObject* m_pGameObject;
	};

}

