#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>
namespace Rius
{
	class RigidBodyComponent :	public BaseComponent
	{
	public:
		RigidBodyComponent(float mass = 0);
		~RigidBodyComponent();
		void AddForce(glm::vec2& force);
		void Bounce(float multiply);
		void Initialize() override;
		void Update() override;
		void Render() const override;
	private:
		float m_Mass;
		glm::vec2 m_AccelerationForce;
		glm::vec2 m_Velocity;
		
	};

	
}

