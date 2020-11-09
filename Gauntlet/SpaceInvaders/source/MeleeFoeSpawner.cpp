#include "MeleeFoeSpawner.h"
MeleeFoeSpawner::MeleeFoeSpawner(Camera* camera, const char* filepath, TileState state, int rowPosition, int columnPosition, int maxRows, Player* player, EnemyManager* enemyManager, SoundSystem* soundSystem) :
	Spawner(camera, filepath, state, rowPosition, columnPosition, maxRows, player, enemyManager, soundSystem)
{
	hitPoints = 300;
	spawnrate = 8;
}

MeleeFoeSpawner::~MeleeFoeSpawner() { }

void MeleeFoeSpawner::SpawnEnemy()
{
	if (enemyCount > 8)
		return;

	for (Tile* tile : spawnArea)
	{
		if (!tile->IsOccupied() && tile->IsPassable())
		{
			Vector2 spawnLocation = tile->GetPosition();

			Enemy* enemy = new MeleeFoe(camera, player, soundSystem);
			enemy->SetPosition(spawnLocation);
			enemy->ResetPreviousPosition();
			tile->Occupy(enemy);
			enemyManager->AddEnemy(enemy);
			enemyCount++;
			break;
		}
	}
}