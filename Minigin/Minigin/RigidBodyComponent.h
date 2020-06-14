#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>
namespace Rius
{
	class RigidBodyComponent final: public BaseComponent
	{
	public:
		RigidBodyComponent(float mass = 0);
		~RigidBodyComponent();
		RigidBodyComponent(const RigidBodyComponent& other);
		RigidBodyComponent(RigidBodyComponent&& other) noexcept = default;
		RigidBodyComponent& operator= (const RigidBodyComponent& other) = default;
		RigidBodyComponent& operator= (RigidBodyComponent&& other) = default;

		void SetComponent(BaseComponent* comp) override;
		BaseComponent* Clone() override;

		void AddForce(glm::vec2 force);
		void Bounce(float multiply);
		void Initialize() override;
		void Update(float deltaT) override;
		void Render() const override;
		void OnCollisionEnter(Collider* collider) override;

		void SetKinematic(bool kinematic);
		glm::vec3& GetVelocity() { return m_Velocity; }
		void ResetUp() { m_Velocity.y = 0; }
		bool IsOnGround();
		void MoveTo(const glm::vec3& location);

		void SetBounceMulti(const float amount) { m_BounceMulti = amount; }
		glm::vec2 GetAcceleration() const { return m_AccelerationForce; }
		void SetAcceleration(const glm::vec2& force) { m_AccelerationForce = force; }
		void SetForce(const glm::vec3& force) { m_Velocity = force; }

	private:
		bool m_Kinematic;
		bool m_OnGround;
		bool m_UpdatePos;
		float m_BounceMulti;
		float m_MaxForce;
		float m_Mass;

		glm::vec2 m_AccelerationForce;
		glm::vec3 m_Velocity;
	};


}

