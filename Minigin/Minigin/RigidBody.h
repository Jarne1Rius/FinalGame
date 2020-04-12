#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>
namespace Rius
{
	class RigidBody :	public BaseComponent
	{
	public:
		RigidBody();
		~RigidBody();
		void Initialize() override;
		void Update() override;
		void Render() const override;
	private:
		float m_Mass;
		glm::vec2 m_AccelerationForce;
		glm::vec2 m_Velocity;
		
	};
}

