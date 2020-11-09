#include "Spawner.h"
Spawner::Spawner(Camera* camera, const char* filepath, TileState state, int rowPosition, int columnPosition, int maxRows, Player* player, EnemyManager* enemyManager, SoundSystem* soundSystem) :
	Tile(camera, filepath, state, rowPosition, columnPosition, maxRows),
	spawnTimer(0),
	player(player),
	enemyManager(enemyManager),
	soundSystem(soundSystem)
{ }

Spawner::~Spawner() { }

void Spawner::DesignateSpawnArea(std::vector<Tile*> area) { spawnArea = area; }

void Spawner::Update(float deltaTime)
{
	if (!destroyed)
	{
		spawnTimer += deltaTime;
		if (spawnTimer > spawnrate)
		{
			spawnTimer = 0;
			SpawnEnemy();
		}
	}
}

void Spawner::Draw() { Entity::Draw(); }

void Spawner::SpawnEnemy() { }

void Spawner::ResolveCollision(Projectile* projectile)
{
	Tile::ResolveCollision(projectile);
	if (projectile->IsPlayers())
	{
		hitPoints -= projectile->GetDamage();
		if (hitPoints <= 0)
			Destroy();
	}
}

void Spawner::Destroy()
{
	soundSystem->PlayEnemyDie();
	destroyed = true;
	filepath = "../resources/images/Floor.png";
	AddSprite();
	state = EMPTY;
}