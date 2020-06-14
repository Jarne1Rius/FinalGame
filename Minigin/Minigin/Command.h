#pragma once
namespace Rius
{
	class GameObject;

	enum TypePress { pressed, release, hold };
	class Command
	{
	public:
		virtual  ~Command() = default;
		virtual void Execute( GameObject* actor, float hit){}
		bool m_Pressed = false;
		TypePress m_Type = TypePress::pressed;
		bool CheckHit(bool hit) const
		{
			switch (m_Type)
			{
			case pressed:
				if (!m_Pressed && hit) return true;
				break;
			case release:
				if (m_Pressed && !hit) return true;
				break;
			case hold:
				if (m_Pressed && hit) return  true;
				break;
			}
			return false;
		}
	};

	class JumpCommand : public Command
	{
	public:
		void Execute( GameObject* actor, float hit) override;

	};
	class FireCommand : public Command
	{
	public:
		void Execute( GameObject* actor, float hit) override;
	};
	class MoveLeft : public Command
	{
	public:
		void Execute( GameObject* actor, float hit) override;
	};
	class MoveRight : public Command
	{
	public:
		void Execute( GameObject* actor, float hit) override;
	};
	class NewPlayerAdd : public Command
	{
	public:
		void Execute( GameObject* actor, float hit) override;
	};
}