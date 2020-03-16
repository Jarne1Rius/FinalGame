#pragma once
#include "SceneManager.h"

namespace Rius
{
	class GameObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(GameObject* object);
		explicit Scene(const std::string& name);

		void Update();
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 

		std::string m_Name;
		std::vector <GameObject*> m_pObjects{};

		static unsigned int m_IdCounter; 
	};

}
