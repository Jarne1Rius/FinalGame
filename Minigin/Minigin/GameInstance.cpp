#include "MiniginPCH.h"
#include "GameInstance.h"

#include "LevelManager.h"
#include "Minigin.h"
#include "HealthComponent.h"
#include "InputManager.h"
#include "PlayerComponent.h"
#include "SceneManager.h"
#include "Scene.h"

Rius::Player& Rius::GameInstance::GetPlayer(int playerId)
{
	if (AmountOfPlayers() < playerId)
		playerId = 0;
	return m_Players[playerId];
}

Rius::Player::Player()
	:IdController(InputManager::GetInstance().GetGamepadId()),m_HealthComponent(),m_color()
{
}

void Rius::Player::Render(TextRenderer* textRenderer, glm::vec2 pos, std::string name) const
{
	pos.y = float(Minigin::m_Height);
	textRenderer->RenderText(pos, name, 1, m_color);
	pos.y -= 30;
	textRenderer->RenderText(pos, std::to_string(score), 1, m_color);
}

void Rius::Player::RemoveHealth(int amount)
{
	m_HealthComponent->RemoveHealth();
	if (m_HealthComponent->CurrentHealth() <= 0)
	{
		dead = true;

		pPlayer->GetTransform().SetPosition(0, -1000, 0);
		//SceneManager::GetInstance().GetCurrentScene()->Remove(pPlayer);
		//pPlayer = nullptr;
	}
	else
	{
		pPlayer->GetComponent<PlayerComponent>()->TakeDamage(amount);
	}
}

void Rius::GameInstance::AddPlayer(GameObject* playerGameObject)
{
	GameObject* p = new GameObject{};
	p->AddComponent(new HealthComponent{ 3,(m_Players.size() < 1) });
	Player player;
	player.pPlayer = playerGameObject;
	player.m_HealthComponent = p->GetComponent < HealthComponent>();
	player.score = 0;
	player.m_color = (m_Players.size() == 0) ? glm::vec3{0, 1, 0} : glm::vec3{0, 0, 1};
	m_Players.push_back(player);
	SceneManager::GetInstance().GetCurrentScene()->Add(p);
	playerGameObject->SetActive(false);
	p->SetActive(false);
	 new GUISystem(p);
}


void Rius::GameInstance::SetPos(GameObject* pPlayer)
{
	for (int i = 0; i < int(m_Players.size()); ++i)
	{
		if (m_Players[i].pPlayer == pPlayer)
		{
			if (!pPlayer->GetActive())
			{
				m_Players[i].m_HealthComponent->GetGameObject()->SetActive(true);
				pPlayer->SetActive(true);
				LevelManager::GetInstance().SetPosition(pPlayer, i);
			}
			break;
		}
	}
}

Rius::Player& Rius::GameInstance::GetPlayer(const GameObject* player)
{
	for (Player& p : m_Players)
	{
		if (p.pPlayer == player)
		{
			return p;
		}
	}
	return m_Players[0];
}


int Rius::GameInstance::EnemiesAlive() const
{
	return int(m_Enemies.size());
}

void Rius::GameInstance::Update()
{

	if ((m_Enemies.size() == 0))
	{
		std::vector<GameObject*> players;
		for (Player& player : m_Players)
		{
			players.push_back(player.pPlayer);
		}
		LevelManager::GetInstance().NextLevel(players);
	}
	else
	{
		bool continueGame{ true };
		for (Player player : m_Players)
		{
			if (player.dead) continueGame = false;
		}
		if (!continueGame)
		{
			std::vector<GameObject*> players;
			for (Player& player : m_Players)
			{
				player.score = 0;
				player.dead = false;
				player.m_HealthComponent->ResetHealth();
				players.push_back(player.pPlayer);
			}
			for (GameObject* enemy : m_Enemies)
			{
				SceneManager::GetInstance().GetCurrentScene()->Remove(enemy);
			}
			LevelManager::GetInstance().ResetLevel(players);
		}
	}
}

void Rius::GameInstance::AddEnemy(GameObject* Enemy)
{
	m_Enemies.push_back(Enemy);

	 new GUISystem(Enemy);
}

void Rius::GameInstance::AddEnemy(std::vector<GameObject*> Enemy)
{
	for (auto&& enemy : Enemy)
	{
		m_Enemies.push_back(enemy);
	}
}

void Rius::GameInstance::SetEnemies(std::vector<GameObject*> Enemy)
{
	m_Enemies = Enemy;
}

void Rius::GameInstance::RemoveEnemy(const GameObject* Enemy)
{
	auto it = std::find(m_Enemies.begin(), m_Enemies.end(), Enemy);
	if (it != m_Enemies.end())
	{
		m_Enemies.erase(it);
	}
}
