#ifndef GENERAL_MANAGER_H
#define GENERAL_MANAGER_H

#include "Player.h"
#include "Map.h"
#include "PlayerChoise.h"

class GeneralManager
{
public:
	GeneralManager(Player* player, Map* map, PlayerChoise playerChoise);
	virtual ~GeneralManager();

	void Update(float deltaTime);

	int GetScore();
	void AddToScore(int points);
	int GetHealth();
	void SetHealth(int health);
	char* GetClass();
	int GetFloor();
	void GetInventory(int& keys, int& potions);
private:
	Player* player;
	Map* map;
	PlayerChoise playerChoise;
	std::vector<ITEM> playerInventory;
	int score, playerHealth, floor;
};
#endif