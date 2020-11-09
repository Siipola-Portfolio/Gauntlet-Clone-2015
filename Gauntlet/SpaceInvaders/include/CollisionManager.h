#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "Player.h"
#include "Map.h"
#include "EnemyManager.h"

//Handles interaction between entities and the map
class CollisionManager
{
public:
	CollisionManager(Map* map, Player* player, EnemyManager* enemyManager);
	virtual ~CollisionManager();

	void UpdatePlayerCollisions(float deltaTime);
	void UpdateEnemyCollisions(float deltaTime);
private:
	//Get adjancent tiles and resolve collisions with them

	void TestPlayerCollision();
	void TestCharacterCollision(Character* character);

	//Check if a collision needs to be resolved with adjacent tiles
	void TestProjectileCollision(Projectile* projectile);

	void GetAdjacentTiles(Entity* entity, int& leftTile, int& rightTile, int& topTile, int& bottomTile);
	bool CollisionBetweenEntities(Entity* A, Entity* B);
	void CharacterOccupyTile(Character* character);
	Tile* GetTileOccupiedByCharacter(Character* character);
	Map* map;
	Player* player;
	EnemyManager* enemyManager;
};
#endif