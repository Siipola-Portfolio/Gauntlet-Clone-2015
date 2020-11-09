#ifndef SPAWNER_H
#define SPAWNER_H

#include "Tile.h"
#include "EnemyManager.h"

class Spawner : public Tile
{
public:
	Spawner(Camera* camera, const char* filepath, TileState state, int rowPosition, int columnPosition, int maxRows, Player* player, EnemyManager* enemyManager, SoundSystem* soundSystem);
	virtual ~Spawner();

	void Update(float deltaTime);
	virtual void Draw();

	virtual void ResolveCollision(Projectile* projectile);
	void DesignateSpawnArea(std::vector<Tile*> area);

protected:
	virtual void SpawnEnemy();
	void Destroy();

	bool destroyed = false;
	float spawnTimer, spawnrate;
	int hitPoints;
	std::vector<Tile*> spawnArea;
	Player* player;
	EnemyManager* enemyManager;

	int enemyCount;
	SoundSystem* soundSystem;
};
#endif