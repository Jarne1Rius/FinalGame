#pragma once
#include<iostream>
#include<string>
#include <fstream>
#include <assert.h>

namespace ReaderAndWriter
{
	inline void BinaryRead(std::ifstream& stream, std::string& value)
	{
		assert(stream.is_open());
		int size{};
		stream.read(reinterpret_cast<char*>(&size), sizeof(int));
		value.resize(size);
		stream.read(&value[0], size);
	}

	inline void BinaryWrite(std::ofstream& stream, const std::string& value)
	{
		assert(stream.is_open());
		int size{ int(value.size()) };
		stream.write(reinterpret_cast<char*>(&size), sizeof(size));
		stream.write(value.c_str(), value.length());
	}
	template<typename T>
	inline void BinaryRead(std::ifstream& stream, T& value)
	{
		assert(stream.is_open());
		stream.read(reinterpret_cast<char*>(&value), sizeof(T));

	}
	template<typename T>
	inline void BinaryWrite(std::ofstream& stream, const T& value)
	{
		assert(stream.is_open());
		stream.write(reinterpret_cast<const char*>(&value), sizeof(T));
	}
}