#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>
namespace Rius
{
	class RigidBodyComponent : public BaseComponent
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
		void Update() override;
		void Render() const override;
		void SetKinematic(bool kinematic);
		glm::vec3& GetVelocity() { return m_Velocity; }
		bool IsOnGround();
	private:
		float m_Mass;
		glm::vec2 m_AccelerationForce;
		glm::vec3 m_Velocity;
		bool m_Kinematic;
		bool m_OnGround;
		float m_MaxForce;
	};


}

