#pragma once
namespace Rius
{
	class UI;

	enum Event
	{
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
		virtual void OnNotify(const GameObject* object, Event event) ;
	};
	class GUISystem : public Observer
	{
	public:
		GUISystem( GameObject* pObject);
		void OnNotify(const GameObject* object, Event event) override;
	private:
	};
}

