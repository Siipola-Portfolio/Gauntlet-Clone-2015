#include "Projectile.h"
#include <iostream>
Projectile::Projectile(Camera* camera, int damage, float velocity, bool isPlayers) :
	Entity(camera),
	damage(damage),
	velocity(velocity),
	LIFE_TIME(4.0f),
	isPlayers(isPlayers),
	canBeRemoved(false)
{
	filepath = "../resources/images/Projectile.png";
	width = height = 8;
	AddSprite();
	isAlive = false;
}

Projectile::~Projectile() { }

void Projectile::Update(float deltaTime)
{
	direction = direction.UnitVector();
	if (isAlive)
	{
		position = position + (direction * (deltaTime * velocity));
		lifeTimer += deltaTime;
		if (lifeTimer > LIFE_TIME)
			isAlive = false;
	}
	Entity::Update(deltaTime);
}

void Projectile::Shoot(Vector2 newPosition)
{
	lifeTimer = 0;
	isAlive = true;
	position = newPosition;
}

void Projectile::Draw() { Entity::Draw(); }


void Projectile::SetDirection(Vector2 direction)
{

	//if direction is diagonal, we reduce magnitude
	if (direction.x != 0 && direction.y != 0)
	{
		if (direction.x > 0)
			direction.x = glm::sqrt(direction.x * direction.x / 2);
		else direction.x = -glm::sqrt(glm::abs(direction.x * direction.x / 2));
		if (direction.y > 0)
			direction.y = glm::sqrt(direction.y * direction.y / 2);
		else direction.y = -glm::sqrt(glm::abs(direction.y * direction.y / 2));
	}
	this->direction = direction;
}

bool Projectile::IsPlayers() { return isPlayers; }

int Projectile::GetDamage() { return damage; }

void Projectile::Delete() { canBeRemoved = true; }

bool Projectile::CanBeRemoved() { return canBeRemoved; }