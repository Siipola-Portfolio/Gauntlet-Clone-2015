#include "Warrior.h"

Warrior::Warrior(Camera* camera, SoundSystem* soundSystem) :
	Player(camera, soundSystem),
	POTION_BONUS(100),
	POTION_TIME(6)
{
	width = height = 32;
	topLeftCoords = Vector2(96, 0);

	health = 350;
	armor = 5;
	velocity = 100;
	damage = 125;
	projectileSpeed = 450;
	firerate = 1.6f;
	hungerrate = 3;

	PostInitialize();
}

Warrior::~Warrior() { }

void Warrior::PostInitialize()
{
	soundSystem->InitPlayerShoot(WARRIOR);
	Player::PostInitialize();
}

void Warrior::Update(float deltaTime)
{
	if (potionActive)
	{
		potionTimer += deltaTime;
		if (potionTimer > POTION_TIME)
		{
			potionActive = false;
			armor -= POTION_BONUS;
		}
	}
	Player::Update(deltaTime);
}

void Warrior::UsePotion()
{
	potionActive = true;
	potionTimer = 0;
	armor += POTION_BONUS;
}