#pragma once
#include "Extra.h"
#include <vector>
#include  "Collider.h"
#include "glm/glm.hpp"
namespace Rius
{
	static std::vector<Collider*> m_AllColliders;

	void AddCollider(Collider* collider)
	{
		m_AllColliders.push_back(collider);
	}
	
	float SqrtMagnitude(const glm::vec3& pos1, const glm::vec3& pos2)
	{
		return pos1.x * pos2.x + pos2.y * pos2.y + pos1.z + pos2.z;
	}
	float SqrtMagnitude(const glm::vec2& pos1, const glm::vec2& pos2)
	{ 
		return pos1.x * pos2.x + pos2.y * pos2.y;
	}
	inline bool Collision(const Rectangle2D& rect1, const Rectangle2D& rect2)
	{
		bool collisionX = rect1.pos.x + rect1.width >= rect2.pos.x &&
			rect2.pos.x + rect2.width >= rect1.pos.x;
		bool collisionY = rect1.pos.y + rect1.height >= rect2.pos.y &&
			rect2.pos.y + rect2.height >= rect1.pos.y;
		return collisionX && collisionY;
	}

	inline bool Collision(const Rectangle3D& rect1,const  Rectangle3D& rect2)
	{
		bool collisionX = rect1.pos.x + rect1.width >= rect2.pos.x &&
			rect2.pos.x + rect2.width >= rect1.pos.x;
		bool collisionY = rect1.pos.y + rect1.height >= rect2.pos.y &&
			rect2.pos.y + rect2.height >= rect1.pos.y;
		bool collisionZ = rect1.pos.z + rect1.depth >= rect2.pos.z &&
			rect2.pos.z + rect2.depth >= rect1.pos.z;
		return collisionX && collisionY && collisionZ;
	}

	inline bool Collision(const Circle2D& circle1, const Circle2D& circle2)
	{
		return SqrtMagnitude(circle1.pos, circle2.pos) < ((circle1.radius + circle2.radius) * (circle1.radius + circle2.radius));
	}

	inline bool Collision(const Circle3D& circle1, const Circle3D& circle2)
	{
		return SqrtMagnitude(circle1.pos, circle2.pos) < ((circle1.radius + circle2.radius) * (circle1.radius + circle2.radius));
	}
	inline bool Collision(const Circle3D& circle1, const Rectangle3D& rectangle3D)
	{
		float x = glm::max(rectangle3D.pos.x, glm::min(circle1.pos.x, rectangle3D.pos.x + rectangle3D.width));
		float y = glm::max(rectangle3D.pos.y, glm::min(circle1.pos.y, rectangle3D.pos.y + rectangle3D.width));
		float z = glm::max(rectangle3D.pos.z, glm::min(circle1.pos.z, rectangle3D.pos.z + rectangle3D.depth));
		glm::vec3 position = {x, y, z};
		return SqrtMagnitude(position, position) < (circle1.radius * circle1.radius);
	}
	inline bool Collision(const Rectangle3D& rectangle3D,const Circle3D& circle1)
	{
		return Collision(circle1, rectangle3D);
	}
	inline bool Collision(const Circle2D& circle1, const Rectangle2D& rectangle3D)
	{
		float x = glm::max(rectangle3D.pos.x, glm::min(circle1.pos.x, rectangle3D.pos.x + rectangle3D.width));
		float y = glm::max(rectangle3D.pos.y, glm::min(circle1.pos.y, rectangle3D.pos.y + rectangle3D.width));
		glm::vec2 position = { x, y };
		return SqrtMagnitude(position, position) < (circle1.radius * circle1.radius);
	}
	inline bool Collision(const Rectangle2D& rectangle3D,const Circle2D& circle1)
	{
		return Collision(circle1, rectangle3D);
	}
	inline bool Collision(const Capsule2D& capsule1, const Capsule2D& capsule2)
	{
		if (Collision(capsule1.Center, capsule2.Center)) return true;
		if (Collision(capsule1.Center, capsule2.Bottom)) return true;
		if (Collision(capsule1.Center, capsule2.Top)) return true;
		if (Collision(capsule1.Top, capsule2.Center)) return true;
		if (Collision(capsule1.Top, capsule2.Bottom)) return true;
		if (Collision(capsule1.Top, capsule2.Top)) return true;
		if (Collision(capsule1.Bottom, capsule2.Center)) return true;
		if (Collision(capsule1.Bottom, capsule2.Bottom)) return true;
		if (Collision(capsule1.Bottom, capsule2.Top)) return true;
		return false;
	}
	inline bool Collision(const Capsule2D& capsule, const Rectangle2D& rectangle2D)
	{
		if (Collision(capsule.Center, rectangle2D)) return true;
		if (Collision(capsule.Center, rectangle2D)) return true;
		if (Collision(capsule.Center, rectangle2D)) return true;
		return false;
	}
	inline bool Collision(const Capsule2D& capsule, const Circle2D& rectangle2D)
	{
		if (Collision(capsule.Center, rectangle2D)) return true;
		if (Collision(capsule.Center, rectangle2D)) return true;
		if (Collision(capsule.Center, rectangle2D)) return true;
		return false;
	}
	
	inline bool Collision(const Capsule3D& capsule1, const Capsule3D& capsule2)
	{
		if (Collision(capsule1.Center, capsule2.Center)) return true;
		if (Collision(capsule1.Center, capsule2.Bottom)) return true;
		if (Collision(capsule1.Center, capsule2.Top)) return true;
		if (Collision(capsule1.Top, capsule2.Center)) return true;
		if (Collision(capsule1.Top, capsule2.Bottom)) return true;
		if (Collision(capsule1.Top, capsule2.Top)) return true;
		if (Collision(capsule1.Bottom, capsule2.Center)) return true;
		if (Collision(capsule1.Bottom, capsule2.Bottom)) return true;
		if (Collision(capsule1.Bottom, capsule2.Top)) return true;
		return false;
	}
	inline bool CheckCollision(const Capsule3D& capsule, const Rectangle3D& rectangle2D)
	{
		if (Collision(capsule.Center, rectangle2D)) return true;
		if (Collision(capsule.Center, rectangle2D)) return true;
		if (Collision(capsule.Center, rectangle2D)) return true;
		return false;
	}
	inline bool CheckCollision(const Capsule3D& capsule, const Circle3D& rectangle2D)
	{
		if (Collision(capsule.Center, rectangle2D)) return true;
		if (Collision(capsule.Center, rectangle2D)) return true;
		if (Collision(capsule.Center, rectangle2D)) return true;
		return false;
	}

}
