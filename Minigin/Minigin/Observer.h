#pragma once
namespace Rius
{
	class UI;

	enum Event
	{
		AddEnemy,
		RemoveEnemy,
		AddPlayer,
		Falling,
		hit,
		addscore,
		
	};
	class GameObject;
	class Observer
	{
	public:
		Observer();
		virtual ~Observer() = default;;
		virtual void OnNotify( GameObject* object, Event event) ;
	};
	class GUISystem : public Observer
	{
	public:
		GUISystem( GameObject* pObject);
		void OnNotify( GameObject* object, Event event) override;
	private:
	};
	class MovingObjectObserver: public Observer
	{
	public:
		MovingObjectObserver(GameObject* pObject);
		void OnNotify(GameObject* object, Event event) override;
	};
}

