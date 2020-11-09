#ifndef SPECIAL_ENEMY_SPAWNER_H
#define SPECIAL_ENEMY_SPAWNER_H

#include "Spawner.h"
#include "Map.h"

class Map;

class SpecialEnemySpawner : public Spawner
{
public:
	SpecialEnemySpawner(Camera* camera, const char* filepath, TileState state, int rowPosition, int columnPosition, int maxRows, Player* player, EnemyManager* enemyManager, SoundSystem* soundSystem, Map* map);
	virtual ~SpecialEnemySpawner();

private:
	virtual void SpawnEnemy();
	Map* map;
};
#endif