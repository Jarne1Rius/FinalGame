#pragma once
#include "Material.h"
#include "Logger.h"
namespace Rius
{
	class MaterialManager
	{
	public:
		static void Clear();
		static void AddMaterial(Material* newMaterial, int id);
		static Material* GetMaterial(int id);
	private:
		MaterialManager() = default;
		static std::map<int, Material*> m_Materials;
	};
}

