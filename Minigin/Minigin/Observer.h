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
		virtual ~Observer() {};
		virtual void OnNotify(const GameObject* object, Event event) ;
	};
	class GUISystem : public Observer
	{
	public:
		GUISystem(UI* ui);
		void OnNotify(const GameObject* object, Event event) override;
	private:
		UI* m_MainUI;
	};
}

