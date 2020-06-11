#include "MiniginPCH.h"
#include "MaterialManager.h"

std::map<int, Rius::Material*> Rius::MaterialManager::m_Materials;
int Rius::MaterialManager::m_ID = 100;
void Rius::MaterialManager::Clear()
{
	for (int i = 0; i <int(m_Materials.size()); ++i)
	{
		delete m_Materials[i];
	}
}

void Rius::MaterialManager::AddMaterial(Material* newMaterial, int id)
{
	m_Materials.insert(std::pair<int, Material*>{id, newMaterial});
}

void Rius::MaterialManager::AddMaterial(Material* newMaterial)
{
	m_Materials.insert(std::pair<int, Material*>{m_ID, newMaterial});
	m_ID++;
}

Rius::Material* Rius::MaterialManager::GetMaterial(int id)
{
	Material* mat = m_Materials.at(id);
	if (mat == nullptr)
		Logger::LogError("Mat not exist");
	return mat;
}