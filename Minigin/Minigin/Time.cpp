#include "MiniginPCH.h"
#include "Time.h"

int Rius::Time::m_FrameCount = 0;
int Rius::Time::m_CurrentFrames = 0;
float Rius::Time::m_Time = 0;
float Rius::Time::m_DeltaTime = 0;

void Rius::Time::UpdateTimer(float deltaTime, int frames)
{
	m_DeltaTime = deltaTime;
	m_Time += deltaTime;
	m_FrameCount += frames;
	if (m_Time >= 1)
	{
		//std::cout << "test\n";
		m_Time -= 1.f;
		m_CurrentFrames = m_FrameCount;
		m_FrameCount = 0;
	}
}
