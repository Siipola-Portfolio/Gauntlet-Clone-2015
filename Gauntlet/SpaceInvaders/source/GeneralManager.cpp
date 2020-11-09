#include "GeneralManager.h"

GeneralManager::GeneralManager(Player* player, Map* map, PlayerChoise playerChoise) :
	player(player),
	score(0),
	map(map),
	playerChoise(playerChoise)
{ }

GeneralManager::~GeneralManager() { }

void GeneralManager::Update(float deltaTime)
{
	playerHealth = player->GetHealth();
	playerInventory = player->GetInventory();
}

int GeneralManager::GetHealth()
{
	return playerHealth;
}

void GeneralManager::AddToScore(int points)
{
	score += points;
}

int GeneralManager::GetScore()
{
	return score;
}

void GeneralManager::SetHealth(int health)
{
	playerHealth = health;
}

int GeneralManager::GetFloor()
{
	return map->GetCurrentLevel();
}

char* GeneralManager::GetClass()
{
	switch (playerChoise)
	{
	case WARRIOR: return "Warrior";
	case THIEF: return "Thief";
	case MAGE: return "Mage";
	case CLERIC: return "Cleric";
	default: assert(false);
		return "Warrior";
	}
}

void GeneralManager::GetInventory(int& keys, int& potions)
{
	for (ITEM item : playerInventory)
	{
		if (item == KEY)
			keys++;
		else if (POTION)
			potions++;
	}
}