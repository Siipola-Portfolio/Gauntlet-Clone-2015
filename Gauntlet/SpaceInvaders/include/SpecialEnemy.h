#ifndef SPECIAL_ENEMY_H
#define SPECIAL_ENEMY_H

#include "RangedFoe.h"
#include "Map.h"

class Map;

class SpecialEnemy : public RangedFoe
{
public:
	SpecialEnemy(Camera* camera, Player* player, SoundSystem* soundSystem, Map* map);
	~SpecialEnemy();
	virtual void PostInitialize();
	virtual void Update(float deltaTime);
	virtual void UpdateMovement(float deltaTime);
	virtual void UpdateAttacking(float deltaTime);

private:
	virtual void Attack();
	virtual void InitializeUVCoords();
	void Teleport();

	float teleportTimer = 0;
	const float TELEPORT_COOLDOWN;
	Map* map;
};
#endif