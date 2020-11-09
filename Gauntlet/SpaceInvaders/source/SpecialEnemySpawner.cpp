#include "SpecialEnemySpawner.h"

SpecialEnemySpawner::SpecialEnemySpawner(Camera* camera, const char* filepath, TileState state, int rowPosition, int columnPosition, int maxRows, Player* player, EnemyManager* enemyManager, SoundSystem* soundSystem, Map* map) :
	Spawner(camera, filepath, state, rowPosition, columnPosition, maxRows, player, enemyManager, soundSystem),
	map(map)
{
	hitPoints = 100;
	spawnrate = 3;
}

SpecialEnemySpawner::~SpecialEnemySpawner() { }

void SpecialEnemySpawner::SpawnEnemy()
{
	if (enemyCount < 1)
	for (Tile* tile : spawnArea)
	{
		if (!tile->IsOccupied() && tile->IsPassable())
		{
			Vector2 spawnLocation = tile->GetPosition();

			RangedFoe* enemy = new SpecialEnemy(camera, player, soundSystem, map);
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