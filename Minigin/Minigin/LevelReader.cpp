#include "MiniginPCH.h"
#include "LevelReader.h"
#include "Minigin.h"
std::vector<std::vector<Rius::Rectangle2D>> Rius::LevelReader::ReadFromObjFile(const std::string fileName)
{
	
	std::ifstream input;
	input.open(fileName, std::ios::in | std::ios::binary);
	std::bitset<800000> a{};
	std::bitset<64> c{};
	unsigned char e;
	if (input.is_open())
	{
		int sum{  };
		
		for (int k = 0; k < 10000; ++k)
		{
			BinaryRead(input, e);
			for (int i = 0; i < 8; ++i)
			{
				if ((e & (1 << (7 - i))) >> (7 - i)) a[i + sum] = true;
			}
			sum += 8;
		}
	}
	std::vector<std::vector<Rius::Rectangle2D>> Levels{};
	for (int i = 0; i < 100; ++i)
	{
		Levels.push_back(LoadLevel(a, i * 800));
	}
	return Levels;

}

std::vector<Rius::Rectangle2D> Rius::LevelReader::LoadLevel(std::bitset<800000>& a, int offset)
{
	float width = float(Minigin::m_Width);
	width /= 32.f;
	float height = float(Minigin::m_Height);
	height /= 27.f;
	std::vector<Rectangle2D> L1;

	bool prev = false;

	for (int i = offset; i < 800 + offset; ++i)
	{
		int k{ i %800};
		if (a[i])
		{
			if (prev)
			{
				L1[L1.size() - 1].width += width;// +width;
			}
			else
			{
				glm::vec2 pos{ (width * (k % 32)),Minigin::m_Height - (height * int(k / 32) + height *3) };
				Rectangle2D rect{ pos, (width),(height) };
				L1.push_back(rect);
			}
		}
		prev = a[i];
		if (k % 32 == 31)
			prev = false;
	}

	//Try to get 3 colliders or so
	size_t size{ L1.size() };
	for (int i = 0; i < int(size); ++i)
	{
		std::vector<Rectangle2D> removing;
		for (Rectangle2D& l1 : L1)
		{
			if (l1 == L1[i]) continue;
			if (glm::abs(L1[i].pos.y - L1[i].height + l1.pos.y) < 0.001f && glm::abs(L1[i].pos.x - l1.pos.x) < 0.001f && L1[i].width == l1.width)
			{
				L1[i].height += height;
				removing.push_back(l1);
			}
		}
		for (Rectangle2D& l1 : removing)
		{
			L1.erase(std::find_if(L1.begin(), L1.end(), [&l1](const Rectangle2D& rect1) { return (rect1.pos == l1.pos && rect1.width == l1.width && rect1.height == l1.height); }));
		}
		size = L1.size();
	}
	return L1;
}
