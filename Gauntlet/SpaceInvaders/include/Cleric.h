#ifndef CLERIC_H
#define CLERIC_H

#include "Player.h"
class Cleric : public Player
{
public:
	Cleric(Camera* camera, SoundSystem* soundSystem);
	virtual ~Cleric();

	virtual void Update(float deltaTime);

private:
	virtual void PostInitialize();
	virtual void UsePotion();
};
#endif