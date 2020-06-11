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
		static void AddMaterial(Material* newMaterial);
		static Material* GetMaterial(int id);
		static int m_ID;
	private:
		MaterialManager() = default;
		static std::map<int, Material*> m_Materials;
	};
}

