#pragma once
#include "GameObject.h"
#include "Singleton.h"
#include "TextRenderer.h"

namespace Rius
{
	class HealthComponent;
	class Player
	{
	public:
		Player();
		void Render(TextRenderer* textRenderer, glm::vec2 pos) const;
		void RemoveHealth();
		GameObject* pPlayer = nullptr;
		HealthComponent* m_Health;
		int score = 0;
		int IdController = -1;
		glm::vec3 m_color = {0,1,0};
	};
	class UI :public Singleton<UI>
	{
	public:
		friend  class Singleton<UI>;
		void Initialize();
		void Update();
		void AddPlayer(const Player& player);
		void Render();
		void Cleanup();
		Player& GetPlayer(int playerId);
		Player& GetPlayer(const GameObject* player);
		int AmountOfPlayers() const { return int(m_Players.size()); }
	private:
		TextRenderer* m_TextRenderer;
		std::vector<Player> m_Players;
		UI();
	};
}
