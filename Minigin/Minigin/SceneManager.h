#pragma once
#include "Singleton.h"
#include <vector>
#include <iostream>
namespace Rius
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void AddScene(Scene* newScene);
		static Scene* GetCurrentScene();
		void Update();
		void Render();
		void LateUpdate();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		static std::vector<Scene*> m_Scenes;
		static int m_ActiveScene;
	};
}
