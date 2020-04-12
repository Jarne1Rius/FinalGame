#pragma once
#include "Singleton.h"

namespace Rius
{
	class Time final : public Singleton<Time>
	{
	public:
		void UpdateTimer(float deltaTime, int frames);
		float GetDeltaTime() const;
		int GetFrames();
	private:
		friend  class Singleton<Time>;
		Time() = default;
		int m_FrameCount = 0;
		int m_CurrentFrames =  0;
		float m_DeltaTime = 0;
	};


}
