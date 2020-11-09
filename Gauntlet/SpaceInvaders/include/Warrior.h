#ifndef WARRIOR_H
#define WARRIOR_H

#include "Player.h"

class Warrior : public Player
{
public:
	Warrior(Camera* camera, SoundSystem* soundSystem);
	virtual ~Warrior();

	virtual void Update(float deltaTime);

private:
	virtual void PostInitialize();
	virtual void UsePotion();

	const int POTION_BONUS, POTION_TIME;
	bool potionActive;
	float potionTimer = 0;
};
#endif