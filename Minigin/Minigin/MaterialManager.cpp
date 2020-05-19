#include "MiniginPCH.h"
#include "MaterialManager.h"

std::map<int, Rius::Material*> Rius::MaterialManager::m_Materials;
void Rius::MaterialManager::Clear()
{
	for (int i = 0; i <int( m_Materials.size()); ++i)
	{
		delete m_Materials[i];
	}
}

void Rius::MaterialManager::AddMaterial(Material* newMaterial, int id)
{
	m_Materials.insert(std::pair<int, Material*>{id, newMaterial});
}

Rius::Material* Rius::MaterialManager::GetMaterial(int id)
{
	Material* mat = m_Materials.at(id);
	if (mat == nullptr)
		Logger::LogError("Mat not exist");
	return mat;
}
