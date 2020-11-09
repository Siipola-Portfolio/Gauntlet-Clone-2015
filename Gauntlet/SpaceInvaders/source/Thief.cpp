#include "Thief.h"

Thief::Thief(Camera* camera, SoundSystem* soundSystem) :
	Player(camera, soundSystem),
	POTION_BONUS(0.5f),
	POTION_TIME(6)
{
	width = height = 32;
	topLeftCoords = Vector2(288, 0);

	health = 200;
	armor = 1;
	velocity = 150;
	damage = 40;
	projectileSpeed = 600;
	firerate = 0.3f;
	hungerrate = 5;

	AddItem(KEY);
	PostInitialize();
}

Thief::~Thief() { }

void Thief::PostInitialize()
{
	soundSystem->InitPlayerShoot(THIEF);
	Player::PostInitialize();
}

void Thief::Update(float deltaTime)
{
	if (potionActive)
	{
		potionTimer += deltaTime;
		if (potionTimer > POTION_TIME)
		{
			potionActive = false;
			firerate += POTION_BONUS;
		}
	}
	Player::Update(deltaTime);
}

void Thief::UsePotion()
{
	potionActive = true;
	potionTimer = 0;
	firerate -= POTION_BONUS;
}