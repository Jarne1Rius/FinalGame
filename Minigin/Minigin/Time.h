#pragma once
namespace Rius
{
	class Time final
	{
	public:
		static void UpdateTimer(float deltaTime);
		static float m_DeltaTime;
		static int m_CurrentFrames;
	private:
		Time() = default;
		static int m_FrameCount;
		static float m_Time;
	};


}
