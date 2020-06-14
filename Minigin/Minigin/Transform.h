#pragma once
#include  "MiniginPCH.h"

#include "BaseComponent.h"


namespace Rius
{
	class Transform final: public BaseComponent
	{
	public:
		Transform();
		Transform(const glm::vec3& position, const glm::vec3& scale);
		Transform(const glm::vec3& position, float xAngle = 0, float yAngle = 0, float zAngle = 0);
		Transform(const glm::vec3& position, float xAngle, float yAngle, float zAngle, const glm::vec3& scale);
		Transform(const Transform& other);
		Transform(Transform&& other) noexcept = default;
		Transform& operator= (const Transform& other) = default;
		Transform& operator= (Transform&& other) = default;
		BaseComponent* Clone() override;
		void SetComponent(BaseComponent * comp) override;
		void Initialize() override ;
		void Update(float deltaT) override;
		void Render() const override;

		
		glm::vec3 GetPosition() const;
		glm::vec3 GetScale() const;
		void SetPosition(float x, float y, float z);
		void SetPosition(const glm::vec3& pos);
		glm::mat4& GetMatrix();
		void Translate(const glm::vec3& newPos);
		
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
