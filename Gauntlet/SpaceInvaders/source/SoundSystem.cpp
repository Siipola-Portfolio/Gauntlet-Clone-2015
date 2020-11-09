#include "SoundSystem.h"
#include <iostream>
#include <assert.h>

SoundSystem::SoundSystem() :
	muted(false)
{
	//Create the main system object
	result = FMOD::System_Create(&system);
	if (result != FMOD_OK)
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));

	//Initialize FMOD
	result = system->init(512, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK)
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));

	//Initialize sounds
	result = system->createSound("../resources/sounds/EnemyDie.wav", FMOD_DEFAULT, 0, &enemyDie);
	if (result != FMOD_OK)
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));

	result = system->createSound("../resources/sounds/PickUp.wav", FMOD_DEFAULT, 0, &pickUp);
	if (result != FMOD_OK)
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));

	result = system->createSound("../resources/sounds/DoorOpen.wav", FMOD_DEFAULT, 0, &doorOpen);
	if (result != FMOD_OK)
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));

	result = system->createSound("../resources/sounds/QuaffPotion.wav", FMOD_DEFAULT, 0, &potion);
	if (result != FMOD_OK)
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));

	result = system->createSound("../resources/sounds/ChangeLevel.wav", FMOD_DEFAULT, 0, &changeLevel);
	if (result != FMOD_OK)
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));

	result = system->createSound("../resources/sounds/GainHealth.wav", FMOD_DEFAULT, 0, &gainHealth);
	if (result != FMOD_OK)
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
}

SoundSystem::~SoundSystem()
{
	system->release();
}

void SoundSystem::InitPlayerShoot(PlayerChoise playerClass)
{
	switch (playerClass)
	{
	case WARRIOR:
		result = system->createSound("../resources/sounds/WarriorProjectile.wav", FMOD_DEFAULT, 0, &shoot);
		if (result != FMOD_OK)
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		break;
	case THIEF:
		result = system->createSound("../resources/sounds/ThiefProjectile.wav", FMOD_DEFAULT, 0, &shoot);
		if (result != FMOD_OK)
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		break;
	case MAGE:
		result = system->createSound("../resources/sounds/MageProjectile.wav", FMOD_DEFAULT, 0, &shoot);
		if (result != FMOD_OK)
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		break;
	case CLERIC:
		result = system->createSound("../resources/sounds/ClericProjectile.wav", FMOD_DEFAULT, 0, &shoot);
		if (result != FMOD_OK)
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		break;
	default: assert(false);
		result = system->createSound("../resources/sounds/WarriorProjectile.wav", FMOD_DEFAULT, 0, &shoot);
		if (result != FMOD_OK)
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		break;
	}
}

void SoundSystem::PlayShoot()
{
	if (!muted)
	{
		result = system->playSound(shoot, 0, false, 0);
		if (result != FMOD_OK)
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	}
}

void SoundSystem::PlayEnemyDie()
{
	if (!muted)
	{
		result = system->playSound(enemyDie, 0, false, 0);
		if (result != FMOD_OK)
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	}
}

void SoundSystem::PlayPickUp()
{
	if (!muted)
	{
		result = system->playSound(pickUp, 0, false, 0);
		if (result != FMOD_OK)
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	}
}

void SoundSystem::PlayDoorOpen()
{
	if (!muted)
	{
		result = system->playSound(doorOpen, 0, false, 0);
		if (result != FMOD_OK)
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	}
}

void SoundSystem::PlayQuaffPotion()
{
	if (!muted)
	{
		result = system->playSound(potion, 0, false, 0);
		if (result != FMOD_OK)
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	}
}
void SoundSystem::PlayChangeLevel()
{
	if (!muted)
	{
		result = system->playSound(changeLevel, 0, false, 0);
		if (result != FMOD_OK)
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	}
}

void SoundSystem::PlayGainHealth()
{
	if (!muted)
	{
		result = system->playSound(gainHealth, 0, false, 0);
		if (result != FMOD_OK)
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	}
}

void SoundSystem::ToggleMute() { muted = !muted; }

bool SoundSystem::IsMuted() { return muted; }