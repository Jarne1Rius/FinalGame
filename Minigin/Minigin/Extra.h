#pragma once
#include <glm/glm.hpp>

#include "Texture2D.h"

namespace Rius
{
	enum class Tag
	{
		Player,
		Ground,
		Interactions,
		Static
	};

	enum PositionUI
	{
		Center,
		LeftTop,
		RightTop,
		LeftBottom,
		RightBottom
	};

	enum KeyFunctions
	{
		Jump,
		Right,
		Left,
		Up,
		Down,
		Shoot
	};

	struct Color
	{
		float r, g, b, a;
		glm::vec4 GetVec4() const { return glm::vec4(r, g, b, a); }
		Color();
		Color(float red, float green, float blue, float alpha) : r(red), b(blue), g(green), a(alpha) {};
	};

	struct Rectangle2D
	{
		Rectangle2D() :pos{ 0,0 }, width{ 0 }, height{ 0 } {};
		Rectangle2D(float x, float y, float widthR, float heightR) : pos(x, y), width(widthR), height(heightR) {};
		Rectangle2D(glm::vec2 position, float widthR, float heightR) : pos(position), width(widthR), height(heightR) {};
		bool operator==(Rectangle2D& rect) { return (pos == rect.pos && width == rect.width && height == rect.height); }
		glm::vec2 pos;
		float width = 10;
		float height = 10;
	};
	inline Rectangle2D ConvertToUVCoordinatess(Rectangle2D rectangle, Texture2D* texture)
	{
		float width{ float(texture->Width) }, height{ float(texture->Height) };
		return { rectangle.pos.x / width, rectangle.pos.y / height, rectangle.width / width, rectangle.height / height };
	}
	struct Rectangle3D
	{
		glm::vec3 pos;
		float width = 10;
		float height = 10;
		float depth = 10;
	};

	struct Circle2D
	{
		glm::vec2 pos;
		float radius = 10;
	};
	struct Circle3D
	{
		glm::vec3 pos;
		float radius = 10;
	};

	struct Capsule2D
	{
		Circle2D Top;
		Circle2D Bottom;
		Rectangle2D	Center;
		void Init()
		{
			Top.pos = glm::vec2(Center.pos.x + Center.width / 2.f, Center.pos.y + Center.height);
			Bottom.pos = glm::vec2(Top.pos.x, Top.pos.y - Center.height);
		}
	};
	struct Capsule3D
	{
		Circle3D Top;
		Circle3D Bottom;
		Rectangle3D	Center;
		void Init()
		{
			Top.pos = glm::vec3(Center.pos.x + Center.width / 2.f, Center.pos.y + Center.height, Center.pos.z + Center.depth / 2.f);
			Bottom.pos = glm::vec3(Top.pos.x, Top.pos.y - Center.height, Top.pos.z);
		}
	};

	struct Ray
	{
		glm::vec3 position;
		glm::vec3 direction;
		float min;
		float max;
		std::vector<Tag> IgnoreTags;
	};
	class GameObject;
	struct HitInfo
	{
		HitInfo() = default;;
		glm::vec3 position{};
		glm::vec3 normal{};
		GameObject* hitObject{ nullptr };
		float length{ 0 };
	};
}
