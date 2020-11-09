#include <Application.h>
#include <iostream>
#include "Player.h"

Player::Player(Camera* camera, SoundSystem* soundSystem) :
	Character(camera, soundSystem),
	skipNextUpdate(false),
	wasMutePressedLastFrame(false),
	wasCtrlPressedLastFrame(false)
{ }

Player::~Player()
{
	for (Projectile* projectile : projectiles)
	{
		delete projectile;
		projectile = nullptr;
	}
}

void Player::PostInitialize()
{
	for (int i = 0; i < 10; i++)
		projectiles.push_back(new Projectile(camera, damage, projectileSpeed, true));
	Character::PostInitialize();
}

void Player::Update(float deltaTime)
{
	if (!skipNextUpdate)
	{
		GetInput(deltaTime);
		UpdateHunger(deltaTime);
		for (Projectile* projectile : projectiles)
			projectile->Update(deltaTime);
	}
	else
		skipNextUpdate = false;

	Character::Update(deltaTime);
}

void Player::LateUpdate(float deltaTime)
{
	for (Projectile* projectile : projectiles)
		projectile->LateUpdate(deltaTime);

	Character::LateUpdate(deltaTime);
}

void Player::Draw()
{
	for (Projectile* projectile : projectiles)
		projectile->Draw();

	Character::Draw();
}

void Player::GetInput(float deltaTime)
{
	Vector2 movement(0, 0);

	NHTV::Application& app = NHTV::Application::GetInstance();

	if (app.IsKeyDown(NHTV::Keys::LEFT))
		movement.x -= velocity * deltaTime;
	if (app.IsKeyDown(NHTV::Keys::RIGHT))
		movement.x += velocity * deltaTime;
	if (app.IsKeyDown(NHTV::Keys::UP))
		movement.y += velocity * deltaTime;
	if (app.IsKeyDown(NHTV::Keys::DOWN))
		movement.y -= velocity * deltaTime;
	if (app.IsKeyDown(NHTV::Keys::SPACE) && fireTimer > firerate)
	{
		Projectile* projectile = GetFreeProjectile();
		if (projectile != NULL)
		{
			Shoot(projectile);
			soundSystem->PlayShoot();
		}
	}
	if (app.IsKeyDown(NHTV::Keys::LEFT_CONTROL) && !wasCtrlPressedLastFrame)
	{
		wasCtrlPressedLastFrame = true;
		if (HavePotion())
			UsePotion();
	}
	else if (!app.IsKeyDown(NHTV::Keys::LEFT_CONTROL))
		wasCtrlPressedLastFrame = false;

	if (app.IsKeyDown(NHTV::Keys::M) && !wasMutePressedLastFrame)
	{
		wasMutePressedLastFrame = true;
		soundSystem->ToggleMute();
	}
	else if (!app.IsKeyDown(NHTV::Keys::M))
		wasMutePressedLastFrame = false;

	if (movement.x != 0 || movement.y != 0)
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

	Move(movement);
	camera->SetDestination(position);
}

Projectile* Player::GetFreeProjectile()
{
	std::vector<Projectile*> reserveProjectiles;
	for (Projectile* projectile : projectiles)
	{
		if (!projectile->GetAlive())
			reserveProjectiles.push_back(projectile);
	}
	if (reserveProjectiles.size() <= 0)
		return NULL;

	return reserveProjectiles.front();
}

void Player::UpdateHunger(float deltaTime)
{
	hungerTimer += deltaTime;
	if (hungerTimer >= hungerrate && hungerrate != -1)
	{
		hungerTimer = 0;
		health--;
		if (health <= 0)
			Die();
	}
}

void Player::ProjectileHit(Projectile* projectile)
{
	if (!projectile->IsPlayers())
	{
		projectile->SetAlive(false);
		TakeDamage(projectile->GetDamage());
		if (health <= 0)
			Die();
	}
}

bool Player::UseKey()
{
	bool foundKey = false;
	for (std::vector<ITEM>::iterator it = inventory.begin(); it != inventory.end(); it++)
		if (*it == KEY)
		{
			//we can remove an element while iterating because we then immediately break from the loop
			inventory.erase(it);
			foundKey = true;
			soundSystem->PlayDoorOpen();
			break;
		}
	return foundKey;
}

bool Player::HavePotion()
{
	bool foundPotion = false;
	for (std::vector<ITEM>::iterator it = inventory.begin(); it != inventory.end(); it++)
		if (*it == POTION)
		{
			//we can remove an element while iterating because we then immediately break from the loop
			inventory.erase(it);
			foundPotion = true;
			soundSystem->PlayQuaffPotion();
			break;
		}
	return foundPotion;
}

void Player::UsePotion() { }

void Player::AddItem(ITEM item)
{
	soundSystem->PlayPickUp();
	inventory.push_back(item);
}

std::vector<ITEM> Player::GetInventory() { return inventory; }

std::vector<Projectile*> Player::GetProjectiles() { return projectiles; }

void Player::SkipNextUpdate() { skipNextUpdate = true; }

void Player::Die() { isAlive = false; }