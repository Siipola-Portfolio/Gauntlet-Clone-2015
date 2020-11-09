#include "Mage.h"

Mage::Mage(Camera* camera, SoundSystem* soundSystem, EnemyManager* enemyManager) :
	Player(camera, soundSystem),
	enemyManager(enemyManager),
	POTION_BONUS(6)
{
	width = height = 32;
	topLeftCoords = Vector2(192, 0);

	health = 200;
	armor = 0;
	velocity = 120;
	damage = 100;
	projectileSpeed = 300;
	firerate = 1;
	hungerrate = 2;

	PostInitialize();
}

Mage::~Mage() { }

void Mage::PostInitialize()
{
	soundSystem->InitPlayerShoot(MAGE);
	Player::PostInitialize();
}

void Mage::Update(float deltaTime)
{
	Player::Update(deltaTime);
}

void Mage::UsePotion()
{
	enemyManager->FreezeEnemies(POTION_BONUS);
}