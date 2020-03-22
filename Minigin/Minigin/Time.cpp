#include "MiniginPCH.h"
#include "Time.h"

void Rius::Time::UpdateTimer(float deltaTime, int frames)
{
	m_DeltaTime += deltaTime;
	m_FrameCount += frames;
	if (m_DeltaTime >= 1)
	{
		m_DeltaTime -= 1.f;
		m_CurrentFrames = m_FrameCount;
		m_FrameCount = 0;
	}
}

float Rius::Time::GetDeltaTime() const
{
	return m_DeltaTime;
}

int Rius::Time::GetFrames()
{
	return m_CurrentFrames;
}
