#pragma once
#include "GameObject.h"
#include "Singleton.h"

namespace Rius
{
	class TextRenderer;
	class HealthComponent;
	class Player
	{
	public:
		Player();
		void Render(TextRenderer* textRenderer, glm::vec2 pos, std::string name) const;
		void RemoveHealth(int amount);
		GameObject* pPlayer = nullptr;
		HealthComponent* m_Health;
		int score = 0;
		int IdController = -1;
		glm::vec3 m_color = { 0,1,0 };
		bool dead = false;
	};
	class GameInstance final : public Singleton<GameInstance>
	{
	public:
		friend class Singleton < GameInstance>;
		std::vector<Player> GetPlayers() const { return m_Players; };
		void AddPlayer(GameObject* playerGameObject);
		void AddPlayer();
		void SetPos(GameObject* pPlayer);
		void SetPlayerPrefab(GameObject* prefab) { m_pPlayerPrefab = prefab; }
		Player& GetPlayer(int playerId);
		Player& GetPlayer(const GameObject* player);
		int AmountOfPlayers() const { return int(m_Players.size()); }
		int EnemiesAlive() const;
		void Update();
		
		void AddEnemy(GameObject* Enemy);
		void AddEnemy(std::vector<GameObject*> Enemy);
		void SetEnemies(std::vector<GameObject*> Enemy);
		void RemoveEnemy(const GameObject* Enemy);
	private:
		GameInstance() = default;
		~GameInstance() = default;
		std::vector<Player> m_Players;
		std::vector<GameObject*> m_Enemies;
		GameObject* m_pPlayerPrefab;
	};
}
