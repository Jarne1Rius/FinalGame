#pragma once
#include "SceneManager.h"
#include "UI.h"
namespace Rius
{
	class GameObject;
	class Scene
	{
	public:
		void AddBackGround(GameObject* pBackground);
		void Add(GameObject* object);
		void Remove(GameObject* object);
		explicit Scene(const std::string& name);

		virtual void Update(float deltaT) = 0;
		void UpdateObjects(float deltaT);
		void LateUpdateObjects();
		virtual void Render() const;
		virtual void Initialize();

		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
		static std::vector <GameObject*> m_pObjects;
	private: 
		void Remove();
		std::string m_Name;
		std::vector<GameObject*> m_ReadyToRemove;
		GameObject* m_pBackground;
		static unsigned int m_IdCounter; 
	};

}
