#pragma once
#include "SceneManager.h"
#include "UI.h"
#include "ThreadPool.h"
namespace Rius
{
	class GameObject;
	class Scene
	{
	public:
		void Add(GameObject* object);
		void Remove(GameObject* object);
		explicit Scene(const std::string& name);

		virtual void Update(float deltaT) = 0;
		void UpdateObjects(float deltaT);
		void LateUpdateObjects();
		virtual void Render() const;
		virtual void Initialize();

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
		static std::vector <GameObject*> m_pObjects;
	private: 

		std::string m_Name;
		ThreadPool m_Pool;

		static unsigned int m_IdCounter; 
	};

}
