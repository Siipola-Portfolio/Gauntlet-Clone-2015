#include "Enemy.h"
#include <iostream>
Enemy::Enemy(Camera* camera, Player* player, SoundSystem* soundSystem) :
	Character(camera, soundSystem),
	player(player)
{
	state = MOVING;
}

Enemy::~Enemy() { }

void Enemy::PostInitialize() { Character::PostInitialize(); }

void Enemy::Update(float deltaTime)
{
	if (IsInScreen() && isAlive)
	{
		if (isFrozen)
		{
			freezeTimer += deltaTime;
			if (freezeTimer > freezeTime)
				isFrozen = false;

			deltaTime = 0;
		}

		fireTimer += deltaTime;
		switch (state)
		{
		case MOVING:
			UpdateMovement(deltaTime);
			break;
		case ATTACKING:
			UpdateAttacking(deltaTime);
			break;
		default:
			assert(false);
			break;
		}
	}

	Character::Update(deltaTime);
}

void Enemy::UpdateMovement(float deltaTime)
{
	Vector2 playerPosition = player->GetPosition();
	MoveTowards(playerPosition, deltaTime);

	if (DistanceToPlayer() < range)
		state = ATTACKING;
}

void Enemy::MoveTowards(Vector2 destination, float deltaTime)
{
	Vector2 direction(0, 0);
	float minDistance = 2.0f;
	if (destination.x > position.x + minDistance)
		direction.x = velocity * deltaTime;
	else if (destination.x < position.x - minDistance)
		direction.x = -velocity * deltaTime;
	if (destination.y > position.y + minDistance)
		direction.y = velocity * deltaTime;
	else if (destination.y < position.y - minDistance)
		direction.y = -velocity * deltaTime;

	if (direction.x != 0 || direction.y != 0)
	{
		animationTimer += deltaTime;
		if (animationTimer > animationRate)
		{
			animationTimer = 0;
			if (++animationState >= 3)
				animationState = 0;
		}
	}
	else
	{
		animationTimer = 0;
		animationState = 1;
	}

	Move(direction);

	//If an axis is close enough, set it equal
	if (glm::abs(destination.x - position.x) < velocity * deltaTime)
		position.x = destination.x;
	if (glm::abs(destination.y - position.y) < velocity * deltaTime)
		position.y = destination.y;

	FacePlayer();
}

void Enemy::UpdateAttacking(float deltaTime)
{
	FacePlayer();
	if (fireTimer > firerate)
	{
		Attack();
		fireTimer = 0;
	}
	
	if (DistanceToPlayer() > range)
		state = MOVING;
}

void Enemy::Attack() { }

void Enemy::FacePlayer()
{
	Vector2 playerPosition = player->GetPosition();
	//If movement on a or y axis is minimal, we don't need diagonal facing
	Vector2 viewDirection = playerPosition - position;
	if (glm::abs(3 * (viewDirection.y)) < glm::abs(viewDirection.x))
		viewDirection.y = 0;
	else if (glm::abs(3 * viewDirection.x) < glm::abs(viewDirection.y))
		viewDirection.x = 0;
	SetFacing(viewDirection);
}

float Enemy::DistanceToPlayer()
{
	Vector2 VectorToPlayer = player->GetPosition() - position;
	return VectorToPlayer.CalculateDistance();
}

void Enemy::Freeze(float time)
{
	isFrozen = true;
	freezeTimer = 0;
	freezeTime = time;
}

void Enemy::ProjectileHit(Projectile* projectile)
{
	if (projectile->IsPlayers())
	{
		projectile->SetAlive(false);
		TakeDamage(projectile->GetDamage());
	}
}

void Enemy::Die()
{
	soundSystem->PlayEnemyDie();
	isAlive = false;
}
