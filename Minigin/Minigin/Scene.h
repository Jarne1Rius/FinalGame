#pragma once
#include "SceneManager.h"

namespace Rius
{
	class GameObject;
	class Scene
	{
	public:
		void Add(GameObject* object);
		explicit Scene(const std::string& name);

		virtual void Update() = 0;
		void UpdateObjects();
		void Render() const;

		virtual ~Scene();
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
