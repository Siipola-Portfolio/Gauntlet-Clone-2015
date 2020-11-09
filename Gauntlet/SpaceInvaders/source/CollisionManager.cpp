#include <iostream>
#include "CollisionManager.h"

CollisionManager::CollisionManager(Map* map, Player* player, EnemyManager* enemyManager) :
	map(map), player(player), enemyManager(enemyManager)
{ }

CollisionManager::~CollisionManager() { }

void CollisionManager::UpdatePlayerCollisions(float deltaTime)
{
	CharacterOccupyTile(player);
	if (player->IsMoving())
		TestPlayerCollision();

	std::vector<Projectile*> playerProjectiles = player->GetProjectiles();
	for (Projectile* projectile : playerProjectiles)
	{
		if (projectile->GetAlive())
			TestProjectileCollision(projectile);
	}
}

void CollisionManager::UpdateEnemyCollisions(float deltaTime)
{
	std::vector<Enemy*> enemies = enemyManager->GetEnemies();
	for (Enemy* enemy : enemies)
	{
		if (!enemy->GetAlive())
			GetTileOccupiedByCharacter(enemy)->Empty();

		if (enemy->IsInScreen() && enemy->IsMoving())
		{
			if (enemy->GetAlive())
			{
				CharacterOccupyTile(enemy);
				TestCharacterCollision(enemy);
			}
		}
	}
	std::vector<Projectile*> enemyProjectiles = enemyManager->GetProjectiles();
	for (Projectile* projectile : enemyProjectiles)
		if (projectile->GetAlive())
			TestProjectileCollision(projectile);
}

void CollisionManager::CharacterOccupyTile(Character* character)
{
	Vector2 previousPosition;
	int prevGridX, prevGridY, tileSize;
	previousPosition = character->GetPreviousPosition();
	tileSize = map->TILE_SIZE;

	prevGridX = static_cast<int>(glm::floor(previousPosition.x / tileSize));
	prevGridY = static_cast<int>(glm::floor(previousPosition.y / tileSize));

	assert(prevGridX >= 0 && prevGridX < map->TILE_COLUMNS && prevGridY >= 0 && prevGridY < map->TILE_ROWS);
	Tile* currentlyOccupied = GetTileOccupiedByCharacter(character);

	Tile* previouslyOccupied = map->GetTile(prevGridX, prevGridY);

	if (currentlyOccupied != previouslyOccupied)
	{
		previouslyOccupied->Empty();
		currentlyOccupied->Occupy(character);
		character->ResetPreviousPosition();
	}
	else if (!currentlyOccupied->IsOccupied())
		currentlyOccupied->Occupy(character);
}

void CollisionManager::TestPlayerCollision()
{
	int leftTile, rightTile, topTile, bottomTile;
	GetAdjacentTiles(player, leftTile, rightTile, topTile, bottomTile);

	for (int y = bottomTile; y <= topTile; y++)
	{
		for (int x = leftTile; x <= rightTile; x++)
		{
			assert(x >= 0 && x < map->TILE_COLUMNS && y >= 0 && y < map->TILE_ROWS);
			Tile* tile = map->GetTile(x, y);
			tile->ResolveCollision(player);
		}
	}
}

void CollisionManager::TestCharacterCollision(Character* character)
{

	int leftTile, rightTile, topTile, bottomTile;
	GetAdjacentTiles(character, leftTile, rightTile, topTile, bottomTile);

	for (int y = bottomTile; y <= topTile; y++)
	{
		for (int x = leftTile; x <= rightTile; x++)
		{
			assert(x >= 0 && x < map->TILE_COLUMNS && y >= 0 && y < map->TILE_ROWS);
			Tile* tile = map->GetTile(x, y);
			tile->ResolveCollision(character);
		}
	}
}

void CollisionManager::TestProjectileCollision(Projectile* projectile)
{
	int leftTile, rightTile, topTile, bottomTile;
	GetAdjacentTiles(projectile, leftTile, rightTile, topTile, bottomTile);

	for (int y = bottomTile; y <= topTile; y++)
	{

		if (y < 0) y = 0;
		if (y >= map->TILE_ROWS) break;

		for (int x = leftTile; x <= rightTile; x++)
		{
			if (x < 0) x = 0;
			if (x >= map->TILE_COLUMNS) break;

			assert(x >= 0 && x < map->TILE_COLUMNS && y >= 0 && y < map->TILE_ROWS);
			Tile* tile = map->GetTile(x, y);
			if (!tile->IsPassable())
				tile->ResolveCollision(projectile);
			//Collide against opposing characters, since they are usually not exactly at their tile's location we make a bit more accurate check
			else if (tile->IsOccupied())
			{
				Character* target = tile->GetOccupant();
				if (target != nullptr)
					if (CollisionBetweenEntities(projectile, target))
						target->ProjectileHit(projectile);
			}
		}
	}
}

void CollisionManager::GetAdjacentTiles(Entity* entity, int& leftTile, int& rightTile, int& topTile, int& bottomTile)
{
	float width, height;
	Vector2 position = entity->GetPosition();
	entity->GetSize(width, height);

	leftTile = static_cast<int>(glm::floor((position.x - width*0.5f) / map->TILE_SIZE));
	rightTile = static_cast<int>(glm::floor((position.x + width*0.5f) / map->TILE_SIZE));
	topTile = static_cast<int>(glm::floor((position.y + height*0.5f) / map->TILE_SIZE));
	bottomTile = static_cast<int>(glm::floor((position.y - height*0.5f) / map->TILE_SIZE));
}

bool CollisionManager::CollisionBetweenEntities(Entity* A, Entity* B)
{
	Vector2 APos, BPos;
	float AWidth, AHeight;
	float BWidth, BHeight;
	APos = A->GetPosition();
	A->GetSize(AWidth, AHeight);
	AWidth *= 0.5f;
	AHeight *= 0.5f;
	BPos = B->GetPosition();
	B->GetSize(BWidth, BHeight);
	BWidth *= 0.5f;
	BHeight *= 0.5f;

	if (APos.x - AWidth < BPos.x + BWidth &&
		APos.x + AWidth > BPos.x - BWidth &&
		APos.y - AHeight < BPos.y + BHeight &&
		APos.y + AHeight > BPos.y - BHeight)
		return true;
	return false;
}

Tile* CollisionManager::GetTileOccupiedByCharacter(Character* character)
{
	int gridX, gridY, tileSize;
	Vector2 position = character->GetPosition();
	tileSize = map->TILE_SIZE;

	gridX = static_cast<int>(glm::floor(position.x / tileSize));
	gridY = static_cast<int>(glm::floor(position.y / tileSize));
	//	std::cout << gridX << ", " << gridY << std::endl;
	assert(gridX >= 0 && gridX < map->TILE_COLUMNS && gridY >= 0 && gridY < map->TILE_ROWS);
	return map->GetTile(gridX, gridY);
}