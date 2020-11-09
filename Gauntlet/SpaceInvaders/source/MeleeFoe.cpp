#include "MeleeFoe.h"
#include <iostream>

MeleeFoe::MeleeFoe(Camera* camera, Player* player, SoundSystem* soundSystem) :
	Enemy(camera, player, soundSystem)
{ 
	width = height = 32;
	topLeftCoords = Vector2(0, 128);
	
	health = 100;
	armor = 2;
	velocity = 100;
	damage = 30;
	range = 30;
	firerate = 2.0f;

	PostInitialize();
}

MeleeFoe::~MeleeFoe() { }

void MeleeFoe::PostInitialize()
{
	AddSprite();
	Enemy::PostInitialize();
}

void MeleeFoe::Update(float deltaTime)
{
	Enemy::Update(deltaTime);
}

void MeleeFoe::Attack()
{
	player->TakeDamage(damage);
}

void MeleeFoe::ProjectileHit(Projectile* projectile)
{
	Enemy::ProjectileHit(projectile);
}