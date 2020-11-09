#ifndef RANGED_FOE_SPAWNER
#define RANGED_FOE_SPAWNER

#include "Spawner.h"

class RangedFoeSpawner : public Spawner
{
public:
	RangedFoeSpawner(Camera* camera, const char* filepath, TileState state, int rowPosition, int columnPosition, int maxRows, Player* player, EnemyManager* enemyManager, SoundSystem* soundSystem);
	virtual ~RangedFoeSpawner();

private:
	virtual void SpawnEnemy();
};
#endif