#ifndef THIEF_H
#define THIEF_H

#include "Player.h"

class Thief : public Player
{
public:
	Thief(Camera* camera, SoundSystem* soundSystem);
	virtual ~Thief();

	virtual void Update(float deltaTime);

private:
	virtual void PostInitialize();
	virtual void UsePotion();

	const int POTION_TIME;
	const float POTION_BONUS;
	bool potionActive;
	float potionTimer = 0;
};
#endif