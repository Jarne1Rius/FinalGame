#pragma once

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
	};

	struct Rectangle2D
	{
		Rectangle2D(float x, float y, float widthR, float heightR): pos(x,y),width(widthR),height(heightR){};
		glm::vec2 pos;
		float width = 10;
		float height = 10;
	};

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
			Top.pos = glm::vec3(Center.pos.x + Center.width / 2.f, Center.pos.y + Center.height, Center.pos.z + Center.depth/2.f);
			Bottom.pos = glm::vec3(Top.pos.x, Top.pos.y - Center.height, Top.pos.z);
		}
	};
}