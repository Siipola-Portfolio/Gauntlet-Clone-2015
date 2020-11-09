#include "RangedFoe.h"
#include <iostream>

RangedFoe::RangedFoe(Camera* camera, Player* player, SoundSystem* soundSystem) :
	Enemy(camera, player, soundSystem)
{
	width = height = 32;
	topLeftCoords = Vector2(192, 128);

	health = 100;
	armor = 0;
	velocity = 100;
	damage = 20;
	range = 300;
	firerate = 5.0f;

	for (int i = 0; i < 3; i++)
		projectiles.push_back(new Projectile(camera, damage, 200, false));

	PostInitialize();
}

RangedFoe::~RangedFoe()
{
	for (Projectile* projectile : projectiles)
		projectile->Delete();
}

void RangedFoe::PostInitialize()
{
	AddSprite();
	Enemy::PostInitialize();
}

void RangedFoe::Update(float deltaTime) { Enemy::Update(deltaTime); }

void RangedFoe::UpdateMovement(float deltaTime)
{
	float minDistance = 6.0f;
	Vector2 playerPos = player->GetPosition();
	MoveTowards(playerPos, deltaTime);

	if ((glm::abs(position.x - playerPos.x) < minDistance || glm::abs(position.y - playerPos.y) < minDistance) && DistanceToPlayer() < range)
		state = ATTACKING;
}

void RangedFoe::UpdateAttacking(float deltaTime)
{
	Enemy::UpdateAttacking(deltaTime);

	float minDistance = 6.0f;
	Vector2 playerPos = player->GetPosition();
	if (glm::abs(position.x - playerPos.x) > minDistance && glm::abs(position.y - playerPos.y) > minDistance)
		state = MOVING;
}

void RangedFoe::Attack()
{
	Projectile* projectile = GetFreeProjectile();
	if (projectile != nullptr)
		Shoot(projectile);
	else
		std::cout << "no projectiles" << std::endl;
}

Projectile* RangedFoe::GetFreeProjectile()
{
	std::vector<Projectile*> reserveProjectiles;
	for (Projectile* projectile : projectiles)
		if (!projectile->GetAlive())
			reserveProjectiles.push_back(projectile);

	if (reserveProjectiles.size() <= 0)
		return nullptr;

	return reserveProjectiles.front();
}

void RangedFoe::ProjectileHit(Projectile* projectile) { Enemy::ProjectileHit(projectile); }

std::vector<Projectile*> RangedFoe::GetProjectiles() { return projectiles; }