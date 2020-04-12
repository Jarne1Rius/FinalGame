#pragma once
#include  "MiniginPCH.h"


namespace Rius
{
	class Transform final
	{
	public:
		Transform();
		Transform(const glm::vec3& position, const glm::vec3& scale);
		Transform(const glm::vec3& position, float xAngle = 0, float yAngle = 0, float zAngle = 0);
		Transform(const glm::vec3& position, float xAngle, float yAngle, float zAngle, const glm::vec3& scale);

		glm::vec3 GetPosition() const;
		void SetPosition(float x, float y, float z);
		void SetPosition(const glm::vec3& pos);
		glm::mat4& GetMatrix();
		
		//const glm::vec3& GetRotation() const { return m_Rotation; }
		//void SetRotation(glm::vec3& rotation);
		//void SetRotation(float x, float y, float z);
		void Rotate(float angle, glm::vec3 rotationAngle);
		void Scale(glm::vec3 scale);
		
	private:
		glm::mat4 m_TransformMatrix{};
		glm::vec3 m_Position{};
		float m_XAngle, m_YAngle, m_ZAngle;
		glm::vec3 m_Scale{};
		glm::vec3 m_TransformedPos{};

		void RotateAllAngles(glm::mat4& trans) const;
	};
}
