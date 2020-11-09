#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "SoundSystem.h"

enum ITEM
{
	KEY,
	POTION
};

class Player : public Character
{
public:
	Player(Camera* camera, SoundSystem* soundSystem);
	virtual ~Player();
	virtual void PostInitialize();

	virtual void Update(float deltaTime);
	virtual void LateUpdate(float deltaTime);
	virtual void Draw();


	virtual void Die();

	virtual void ProjectileHit(Projectile* projectile);

	//true if succeeded
	bool UseKey();
	void AddItem(ITEM item);
	std::vector<ITEM> GetInventory();
	std::vector<Projectile*> GetProjectiles();
	void SkipNextUpdate();

protected:
	virtual void UsePotion();
	float hungerrate, projectileSpeed, hungerTimer = 0;

private:
	Projectile* GetFreeProjectile();
	void GetInput(float deltaTime);
	void UpdateHunger(float deltaTime);
	bool HavePotion();

	std::vector<ITEM> inventory;
	std::vector<Projectile*> projectiles;
	bool skipNextUpdate;
	bool wasMutePressedLastFrame, wasCtrlPressedLastFrame;
};
#endif