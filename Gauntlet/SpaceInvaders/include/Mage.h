#ifndef MAGE_H
#define MAGE_H

#include "Player.h"
#include "EnemyManager.h"

class Mage : public Player
{
public:
	Mage(Camera* camera, SoundSystem* soundSystem, EnemyManager* enemyManager);
	virtual ~Mage();

	virtual void Update(float deltaTime);

private:
	virtual void PostInitialize();
	virtual void UsePotion();

	EnemyManager* enemyManager;
	const float POTION_BONUS;
};
#endif