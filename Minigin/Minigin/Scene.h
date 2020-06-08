#pragma once
#include "SceneManager.h"
#include "UI.h"
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
		void LateUpdateObjects();
		 virtual void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
		static std::vector <GameObject*> m_pObjects;
	private: 

		std::string m_Name;
		

		static unsigned int m_IdCounter; 
	};

}
