#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H

#include <fmod.hpp>
#include <fmod_errors.h>
#include "PlayerChoise.h"

class SoundSystem
{
public:
	SoundSystem();
	virtual ~SoundSystem();

	void InitPlayerShoot(PlayerChoise playerClass);
	void PlayShoot();
	void PlayEnemyDie();
	void PlayPickUp();
	void PlayDoorOpen();
	void PlayQuaffPotion();
	void PlayChangeLevel();
	void PlayGainHealth();

	void ToggleMute();
	bool IsMuted();
private:	
	FMOD::System* system;
	FMOD::Sound *shoot, *enemyDie, *pickUp, *doorOpen, *potion, *changeLevel, *gainHealth;
	FMOD_RESULT result;
	bool muted;
};
#endif