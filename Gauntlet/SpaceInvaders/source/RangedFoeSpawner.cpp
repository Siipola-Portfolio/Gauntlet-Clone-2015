#include "RangedFoeSpawner.h"
#include "RangedFoe.h"

RangedFoeSpawner::RangedFoeSpawner(Camera* camera, const char* filepath, TileState state, int rowPosition, int columnPosition, int maxRows, Player* player, EnemyManager* enemyManager, SoundSystem* soundSystem) :
	Spawner(camera, filepath, state, rowPosition, columnPosition, maxRows, player, enemyManager, soundSystem)
{
	hitPoints = 300;
	spawnrate = 6;
}

RangedFoeSpawner::~RangedFoeSpawner() { }

void RangedFoeSpawner::SpawnEnemy()
{
	if (enemyCount > 10)
		return;

	for (Tile* tile : spawnArea)
	{
		if (!tile->IsOccupied() && tile->IsPassable())
		{
			Vector2 spawnLocation = tile->GetPosition();

			RangedFoe* enemy = new RangedFoe(camera, player, soundSystem);
			std::vector<Projectile*> projectiles = enemy->GetProjectiles();
			enemy->SetPosition(spawnLocation);
			enemy->ResetPreviousPosition();
			tile->Occupy(enemy);
			enemyManager->AddEnemy(enemy);
			enemyManager->AddProjectiles(projectiles);
			enemyCount++;
			break;
		}
	}
}