#include "SpecialEnemy.h"
#include "Map.h"
#include <iostream>

SpecialEnemy::SpecialEnemy(Camera* camera, Player* player, SoundSystem* soundSystem, Map* map) :
	RangedFoe(camera, player, soundSystem),
	map(map),
	TELEPORT_COOLDOWN(5)
{
	filepath = "../resources/images/SpecialMonster.png";
	topLeftCoords = { 10, 10 };

	width = height = 32;
	health = 150;
	armor = 2;
	velocity = 80;
	damage = 30;
	range = 200;
	firerate = 2.0f;

	PostInitialize();
}

SpecialEnemy::~SpecialEnemy() { }

void SpecialEnemy::PostInitialize()
{
	AddSprite();
	InitializeUVCoords();
}

void SpecialEnemy::Update(float deltaTime)
{
	teleportTimer += deltaTime;
	if (teleportTimer >= TELEPORT_COOLDOWN && DistanceToPlayer() < range)
	{
		teleportTimer = 0;
		Teleport();
	}
	RangedFoe::Update(deltaTime);
}

void SpecialEnemy::UpdateMovement(float deltaTime) { Enemy::UpdateMovement(deltaTime); }

void SpecialEnemy::UpdateAttacking(float deltaTime) { Enemy::UpdateAttacking(deltaTime); }

void SpecialEnemy::Attack()
{
	Vector2 vectorToPlayer = player->GetPosition() - position;
	Projectile* projectile = GetFreeProjectile();
	if (projectile != nullptr)
		Shoot(projectile, vectorToPlayer);
	else
		std::cout << "no projectiles" << std::endl;
}

void SpecialEnemy::InitializeUVCoords()
{
	float spriteWidth = width * 2;
	float spriteHeight = height * 2;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			uvCoords[i][j].x = topLeftCoords.x + spriteWidth * j;
			uvCoords[i][j].y = topLeftCoords.y + spriteHeight * i;
			//The spritesheet has a lot of empty space so we cut some
			uvCoords[i][j].width = spriteWidth - 20;
			uvCoords[i][j].height = spriteHeight - 10;
		}
	SetFacing(Vector2(0, 1));
}

void SpecialEnemy::Teleport()
{
	Vector2 playerPos, wantedPos, distanceToPlayer, playerRelativePos;
	playerPos = player->GetPosition();
	distanceToPlayer = playerPos - position;
	playerRelativePos = distanceToPlayer.UnitVector();
	wantedPos = position - (playerRelativePos * range);

	int wantedTileX = static_cast<int>(glm::floor(wantedPos.x / map->TILE_SIZE));
	int wantedTileY = static_cast<int>(glm::floor(wantedPos.y / map->TILE_SIZE));

	//ensure we don't try to get a tile out of bounds
	if (wantedTileX <= 0)
		wantedTileX = 1;
	else if (wantedTileX >= map->TILE_COLUMNS)
		wantedTileX = map->TILE_COLUMNS - 2;
	if (wantedTileY <= 0)
		wantedTileY = 1;
	else if (wantedTileY >= map->TILE_ROWS)
		wantedTileY = map->TILE_ROWS - 2;

	int gridX = static_cast<int>(glm::floor(position.x / map->TILE_SIZE));
	int gridY = static_cast<int>(glm::floor(position.y / map->TILE_SIZE));

	Tile *wantedTile, *occupiedTile;
	wantedTile = map->GetTile(wantedTileX, wantedTileY);
	occupiedTile = map->GetTile(gridX, gridY);

	while (wantedTile != occupiedTile)
	{
		if (wantedTile->IsPassable() && !wantedTile->IsOccupied())
			break;	//We have found our tile

		if (gridX < wantedTileX)
			wantedTileX--;
		else wantedTileX++;

		if (gridY < wantedTileY)
			wantedTileY--;
		else wantedTileY++;

		wantedTile = map->GetTile(wantedTileX, wantedTileY);
	}

	position = wantedTile->GetPosition();
}