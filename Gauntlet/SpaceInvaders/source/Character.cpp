#include <iostream>
#include "Character.h"

Character::Character(Camera* camera, SoundSystem* soundSystem) :
	Entity(camera),
	soundSystem(soundSystem),
	isMoving(false),
	animationRate(0.2f)
{
	filepath = "../resources/images/SpriteSheet.png";
	PostInitialize();
}

Character::~Character() { }

void Character::PostInitialize()
{
	AddSprite();
	InitializeUVCoords();
	Entity::PostInitialize();
}
void Character::InitializeUVCoords()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
		{
			uvCoords[i][j].x = topLeftCoords.x + width * j;
			uvCoords[i][j].y = topLeftCoords.y + height * i;
			uvCoords[i][j].width = width;
			uvCoords[i][j].height = height;
		}
	SetFacing(Vector2(0, 1));
}

void Character::Update(float deltaTime)
{
	fireTimer += deltaTime;
	Entity::Update(deltaTime);
}

void Character::LateUpdate(float deltaTime)
{
	Entity::LateUpdate(deltaTime);
}

void Character::Draw()
{
	Entity::Draw();
}

void Character::Move(Vector2 movement)
{
	SetFacing(movement);
	isMoving = true;
	//if moving diagonally, we want to be slower
	if (movement.x != 0 && movement.y != 0)
	{
		if (movement.x > 0)
			movement.x = glm::sqrt(movement.x * movement.x / 2);
		else movement.x = -glm::sqrt(glm::abs(movement.x * movement.x / 2));
		if (movement.y > 0)
			movement.y = glm::sqrt(movement.y * movement.y / 2);
		else movement.y = -glm::sqrt(glm::abs(movement.y * movement.y / 2));
	}
	else if (movement.x == 0 && movement.y == 0)
		isMoving = false;

	position = position + movement;
}

void Character::Shoot(Projectile* projectile)
{
	if (fireTimer < firerate)
		return;

	fireTimer = 0;

	Vector2 dir;
	switch (facing)
	{
	case UP: dir.x = 0; dir.y = 1; break;
	case UPRIGHT: dir.x = dir.y = 1; break;
	case RIGHT: dir.x = 1; dir.y = 0; break;
	case DOWNRIGHT: dir.x = 1; dir.y = -1; break;
	case DOWN:  dir.x = 0; dir.y = -1; break;
	case DOWNLEFT:  dir.x = -1; dir.y = -1; break;
	case LEFT: dir.x = -1; dir.y = 0; break;
	case UPLEFT:  dir.x = -1; dir.y = 1; break;
	}
	projectile->SetDirection(dir);
	projectile->Shoot(position);
}

void Character::Shoot(Projectile* projectile, Vector2 direction)
{
	if (fireTimer < firerate)
		return;

	projectile->SetDirection(direction);
	projectile->Shoot(position);
}

void Character::ResetPreviousPosition()
{
	previousPosition.x = position.x;
	previousPosition.y = position.y;
}

void Character::ProjectileHit(Projectile* projectile) { }

void Character::TakeDamage(int amount)
{
	int healthLost = amount - armor;
	if (healthLost < 1)
		healthLost = 1;

	health -= healthLost;
	if (health <= 0)
		Die();
}

void Character::AddHealth(int amount)
{
	soundSystem->PlayGainHealth();
	health += amount;
}

void Character::Die() { }

void Character::SetFacing(Vector2 dir)
{

	if (dir.x == 0 && dir.y > 0)
	{
		facing = UP;
		spriteDirection = 3;
	}
	else if (dir.x > 0 && dir.y > 0)
	{
		facing = UPRIGHT;
		spriteDirection = 3;
	}
	else if (dir.x > 0 && dir.y == 0)
	{
		facing = RIGHT;
		spriteDirection = 2;
	}
	else if (dir.x > 0 && dir.y < 0)
	{
		facing = DOWNRIGHT;
		spriteDirection = 0;
	}
	else if (dir.x == 0 && dir.y < 0)
	{
		facing = DOWN;
		spriteDirection = 0;
	}
	else if (dir.x < 0 && dir.y < 0)
	{
		facing = DOWNLEFT;
		spriteDirection = 0;
	}
	else if (dir.x < 0 && dir.y == 0)
	{
		facing = LEFT;
		spriteDirection = 1;
	}
	else if (dir.x < 0 && dir.y > 0)
	{
		facing = UPLEFT;
		spriteDirection = 3;
	}

	NHTV::Rect coords = GetCorrectUVCoords();
	NHTV::SpriteManager* spriteManager = NHTV::SpriteManager::GetInstance();
	if (spriteManager)
		spriteManager->SetSpriteUVCoordinates(spriteHandle, coords);
}

bool Character::IsMoving() { return isMoving; }
int Character::GetHealth() { return health; }

Vector2 Character::GetPreviousPosition() { return previousPosition; }

NHTV::Rect Character::GetCorrectUVCoords() { return uvCoords[spriteDirection][animationState]; }