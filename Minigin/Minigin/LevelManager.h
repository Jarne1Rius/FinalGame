#pragma once
#include "Extra.h"
#include <vector>

#include "Singleton.h"
#include <string>

namespace Rius
{
	class Scene;
	class TextureMaterial;

	class Level final
	{
	public:
		Level(std::vector<Rectangle2D> walls, int levelID, TextureMaterial* materialSmall, TextureMaterial* materialBig, std::string locationBigTexture, std::string locationSmallTexture,const std::vector<glm::vec3>& posEnemies, const std::vector<glm::vec2>& startPos = { {100, 70},{600,70} });
		void Initialize();
		void StartLevel(GameObject* pPlayer);
		void StartLevel(std::vector<GameObject*> pPlayer);
		void EndLevel();
		void SetPosition(GameObject* pPlayer, int id);
		GameObject* GetGameObject() const { return m_pBackGround; }
	private:
		void CreateEnemy(const glm::vec3& pos);
		int m_LevelID;
		std::vector<Rectangle2D> m_Walls;
		std::vector<glm::vec3> m_AI;
		std::vector<glm::vec2> m_StartPos;
		GameObject* m_pBackGround;
		TextureMaterial* m_MaterialSmall;
		TextureMaterial* m_MaterialBig;
		std::string m_BigTexture, m_SmallTexture;

		void InitLevel();
	};
	class LevelManager final : public Singleton<LevelManager>
	{
	public:
		friend  class Singleton<LevelManager>;
		void LoadLevels(const std::string& location, const std::string& locationsBigTextures, const std::string& locationSmallTextures, Scene* scene);
		void SetLevel(int level, GameObject* pPlayer);
		void NextLevel(GameObject* pPlayer);
		void NextLevel(std::vector<GameObject*> pPlayer);
		void ResetLevel(std::vector<GameObject*> pPlayer);
		void ResetLevel(GameObject* pPlayer);
		void QuitLevel();
		void SetPosition(GameObject* pPlayer, int id);
	private:
		LevelManager();
		~LevelManager();
		std::vector<Level*> m_Levels;
		int m_CurrentLevel;
	};
}
