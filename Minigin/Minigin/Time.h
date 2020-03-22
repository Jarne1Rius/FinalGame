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
		int m_FrameCount;
		int m_CurrentFrames;
		float m_DeltaTime;
	};


}
