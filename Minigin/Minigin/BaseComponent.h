#pragma once
class GameObject;
class BaseComponent
{
public:
	BaseComponent();
	virtual ~BaseComponent() = default;

	GameObject* GetGameObject() const { return m_pGameObject; };
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() const = 0;
	
protected:
	GameObject* m_pGameObject;
};

