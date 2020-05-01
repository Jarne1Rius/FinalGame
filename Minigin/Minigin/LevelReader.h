#pragma once
#include <bitset>
#include <string>
#include <fstream>

#include "Extra.h"

namespace Rius
{
	class LevelReader
	{
	public:
		std::vector<std::vector<Rectangle2D>> ReadFromObjFile(const std::string filename);
		std::vector<Rectangle2D> LoadLevel(std::bitset<800000>& a, int offset = 0);
	};
	
	inline void BinaryRead(std::ifstream& stream, std::string& value)
	{
		assert(stream.is_open());
		int size{};
		stream.read(reinterpret_cast<char*>(&size), sizeof(int));
		value.resize(size);
		stream.read(&value[0], size);
	}	
	template<typename T>
	inline void BinaryRead(std::ifstream& stream, T& value)
	{
		assert(stream.is_open());
		stream.read(reinterpret_cast<char*>(&value), sizeof(T));

	}

}


