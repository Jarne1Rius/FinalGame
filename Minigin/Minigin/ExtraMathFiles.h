#pragma once
#include "Extra.h"
#include <vector>
#include "Collider.h"
#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>
#include "BoxCollider2D.h"
#include "CircleCollider2D.h"
namespace Rius
{
	inline float MagnitudeSqrt(const glm::vec3& pos1, const glm::vec3& pos2)
	{
		return pos1.x * pos2.x + pos2.y * pos2.y + pos1.z + pos2.z;
	}

	inline float MagnitudeSqrt(const glm::vec2& pos1, const glm::vec2& pos2)
	{
		return pos1.x * pos2.x + pos2.y * pos2.y;
	}
	inline float MagnitudeSqrt(const glm::vec2& vec)
	{
		return vec.x * vec.x + vec.y * vec.y;
;	}
	inline bool Collision(const Rectangle2D& rect1, const Rectangle2D& rect2, glm::vec3& velocityRect1, glm::vec3& velocityRect2)
	{
		bool hit = false;

		glm::vec3 velR1 = velocityRect1;
		if (MagnitudeSqrt(velR1) > 0)
			velR1 = glm::normalize(velocityRect1);
		glm::vec3 velR2 = velocityRect2;
		if (MagnitudeSqrt(velR2) > 0)
			velR2 = glm::normalize(velocityRect2);
		if (rect1.pos.x + rect1.width + velR1.x > rect2.pos.x + velR2.x &&
			rect1.pos.x + velR1.x < rect2.pos.x + rect2.width + velR2.x &&
			rect1.pos.y + rect1.height > rect2.pos.y &&
			rect1.pos.y < rect2.pos.y + rect2.height)
		{
			velocityRect1.x *= -1;
			velocityRect2.x *= -1;
			hit = true;
		}
		if (rect1.pos.x + rect1.width > rect2.pos.x &&
			rect1.pos.x < rect2.pos.x + rect2.width &&
			rect1.pos.y + rect1.height - velR1.y > rect2.pos.y - velR2.y &&
			rect1.pos.y - velR1.y < rect2.pos.y + rect2.height - velR2.y)
		{
			velocityRect1.y *= -1;
			velocityRect2.y *= -1;
			hit = true;
		}
		return hit;
	}

	inline bool Collision(const Rectangle3D& rect1, const  Rectangle3D& rect2)
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
		return MagnitudeSqrt(circle1.pos, circle2.pos) < ((circle1.radius + circle2.radius) * (circle1.radius + circle2.radius));
	}

	inline bool Collision(const Circle3D& circle1, const Circle3D& circle2)
	{
		return MagnitudeSqrt(circle1.pos, circle2.pos) < ((circle1.radius + circle2.radius) * (circle1.radius + circle2.radius));
	}
	inline bool Collision(const Circle3D& circle1, const Rectangle3D& rectangle3D)
	{
		float x = glm::max(rectangle3D.pos.x, glm::min(circle1.pos.x, rectangle3D.pos.x + rectangle3D.width));
		float y = glm::max(rectangle3D.pos.y, glm::min(circle1.pos.y, rectangle3D.pos.y + rectangle3D.width));
		float z = glm::max(rectangle3D.pos.z, glm::min(circle1.pos.z, rectangle3D.pos.z + rectangle3D.depth));
		glm::vec3 position = { x, y, z };
		return MagnitudeSqrt(position, position) < (circle1.radius * circle1.radius);
	}
	inline bool Collision(const Rectangle3D& rectangle3D, const Circle3D& circle1)
	{
		return Collision(circle1, rectangle3D);
	}
	inline bool Collision(const Circle2D& circle1, const Rectangle2D& rectangle3D)
	{
		float x = glm::max(rectangle3D.pos.x, glm::min(circle1.pos.x, rectangle3D.pos.x + rectangle3D.width));
		float y = glm::max(rectangle3D.pos.y, glm::min(circle1.pos.y, rectangle3D.pos.y + rectangle3D.width));
		glm::vec2 position = { x, y };
		return MagnitudeSqrt(position, position) < (circle1.radius * circle1.radius);
	}
	inline bool Collision(const Rectangle2D& rectangle3D, const Circle2D& circle1)
	{
		return Collision(circle1, rectangle3D);
	}
	inline bool Collision(const Capsule2D& capsule1, const Capsule2D& capsule2)
	{
		glm::vec3 vel{ 0,0,0 };
		if (Collision(capsule1.Center, capsule2.Center, vel, vel)) return true;
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
		glm::vec3 vel{ 0,0,0 };
		if (Collision(capsule.Center, rectangle2D, vel, vel)) return true;
		if (Collision(capsule.Center, rectangle2D, vel, vel)) return true;
		if (Collision(capsule.Center, rectangle2D, vel, vel)) return true;
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

	inline bool CheckHit(Circle2D circle2D, Ray& raycast, HitInfo& info)
	{
		float A = glm::dot(raycast.direction, raycast.direction);
		glm::vec2 dir = raycast.direction;
		dir *= 2;
		float B = glm::dot(dir, (circle2D.pos - glm::vec2(raycast.position)));
		float C = glm::dot(circle2D.pos - glm::vec2(raycast.position), circle2D.pos - glm::vec2(raycast.position)) - circle2D.radius * circle2D.radius;
		float discriminant = B * B - 4 * A * C;
		if (discriminant >= 0)
		{
			float t = ((-B - sqrt(discriminant)) / (2 * A));
			if (t < info.length)return false;
			glm::vec3 pos = raycast.position + t * raycast.direction;
			info.position = pos;
			info.length = t;
			return true;
		}
		return false;
	}

	//https://en.wikipedia.org/wiki/Liang%E2%80%93Barsky_algorithm
	inline bool CheckHit(Rectangle2D rectangle, Ray& raycast, HitInfo& info)
	{
		float p1 = -(raycast.direction.x * raycast.max);
		float p2 = -p1;
		float p3 = -(raycast.direction.y * raycast.max);
		float p4 = -p3;

		float q1 = raycast.position.x - rectangle.pos.x;
		float q2 = (rectangle.pos.x + rectangle.width) - raycast.position.x;
		float q3 = raycast.position.y - rectangle.pos.y;
		float q4 = (rectangle.pos.y + rectangle.height) - raycast.position.y;

		float posarr[5], negarr[5];
		int posind = 1, negind = 1;
		posarr[0] = 1;
		negarr[0] = 0;


		if ((p1 == 0 && q1 < 0) || (p2 == 0 && q2 < 0) || (p3 == 0 && q3 < 0) || (p4 == 0 && q4 < 0))
		{
			return false;
		}
		if (p1 != 0) {
			float r1 = q1 / p1;
			float r2 = q2 / p2;
			if (p1 < 0) {
				negarr[negind++] = r1; // for negative p1, add it to negative array
				posarr[posind++] = r2; // and add p2 to positive array
			}
			else {
				negarr[negind++] = r2;
				posarr[posind++] = r1;
			}
		}
		if (p3 != 0) {
			float r3 = q3 / p3;
			float r4 = q4 / p4;
			if (p3 < 0) {
				negarr[negind++] = r3;
				posarr[posind++] = r4;
			}
			else {
				negarr[negind++] = r4;
				posarr[posind++] = r3;
			}
		}

		float xn1, yn1;
		float rn1, rn2;
		rn1 = *std::max_element(negarr, negarr + negind); // maximum of negative array
		rn2 = *std::min_element(posarr, posarr + posind); // minimum of positive array

		if (rn1 > rn2)
			return false;

		xn1 = raycast.position.x + p2 * rn1;
		yn1 = raycast.position.y + p4 * rn1;
		float xl = raycast.position.x - xn1;
		float yl = raycast.position.y - yn1;
		float length = xl * xl + yl * yl;
		if (info.length < length)
		{
			info.length = length;
			info.position = { xn1,yn1,0 };
			return true;
		}
		return false;
	}
	inline HitInfo& RayCast(Ray& raycast)
	{
		std::vector<GameObject*> allGameObjects = SceneManager::GetCurrentScene()->m_pObjects;
		HitInfo info;
		info.length = FLT_MAX;
		for (Collider* Collider : Collider::m_AllColliders)
		{
			BoxCollider2D* box = reinterpret_cast<BoxCollider2D*>(Collider);
			if (box)
			{
				CheckHit(box->GetRectangle(), raycast, info);
				continue;
			}
			CircleCollider2D* circle = reinterpret_cast<CircleCollider2D*>(Collider);
			if (circle)
			{
				CheckHit(circle->GetCircle2D(), raycast, info);
				continue;
			}


		}
	}
}
