#ifndef MELEE_FOE_SPAWNER
#define MELEE_FOE_SPAWNER

#include "Spawner.h"
#include "MeleeFoe.h"
#include "SpecialEnemy.h"

class Map;

class MeleeFoeSpawner : public Spawner
{
public:
	MeleeFoeSpawner(Camera* camera, const char* filepath, TileState state, int rowPosition, int columnPosition, int maxRows, Player* player, EnemyManager* enemyManager, SoundSystem* soundSystem);
	virtual ~MeleeFoeSpawner();

private:
	virtual void SpawnEnemy();
};
#endif