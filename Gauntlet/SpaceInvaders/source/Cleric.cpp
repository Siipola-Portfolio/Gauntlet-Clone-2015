#include "Cleric.h"

Cleric::Cleric(Camera* camera, SoundSystem* soundSystem) :
	Player(camera, soundSystem)
{
	width = height = 32;
	topLeftCoords = Vector2(0, 0);

	health = 400;
	armor = 2;
	velocity = 120;
	damage = 60;
	projectileSpeed = 500;
	firerate = 0.8f;
	hungerrate = -1;

	PostInitialize();
}

Cleric::~Cleric() { }

void Cleric::PostInitialize()
{
	soundSystem->InitPlayerShoot(CLERIC);
	Player::PostInitialize();
}

void Cleric::Update(float deltaTime)
{
	Player::Update(deltaTime);
}

void Cleric::UsePotion()
{
	health += 50;
}