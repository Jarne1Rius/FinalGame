#pragma once
#include  "MiniginPCH.h"
namespace Rius
{
	class Transform final
	{
	public:
		Transform(const glm::vec3& position) : m_Position(position){};
		Transform():m_Position(){};
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);
	private:
		glm::vec3 m_Position;
	};
}
