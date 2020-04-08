#pragma once
#include  "MiniginPCH.h"
namespace Rius
{
	class Transform final
	{
	public:
		Transform(const glm::vec3& position) : m_Position(position){};
		Transform():m_Position(){};
		void Update();
		const glm::vec3& GetPosition() const;
		void SetPosition(float x, float y, float z);
		void SetPosition(const glm::vec3& pos);

		const glm::vec3& GetRotation() const { return m_Rotation; }
		void SetRotation(glm::vec3& rotation);
		void SetRotation(float x, float y, float z);
		
	private:
		glm::mat4 m_TransformMatrix;
		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
		glm::vec3 m_Scale;
		glm::vec3 m_TransformedPos;
	};
}
