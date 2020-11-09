#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "Player.h"

enum EnemyState
{
	MOVING,
	ATTACKING
};
class Enemy : public Character
{
public:
	Enemy(Camera* camera, Player* player, SoundSystem* soundSystem);
	virtual ~Enemy();
	virtual void PostInitialize();

	virtual void Update(float deltaTime);
	virtual void ProjectileHit(Projectile* projectile);
	virtual void Die();

	void Freeze(float time);
protected:
	virtual void UpdateMovement(float deltaTime);
	virtual void UpdateAttacking(float deltaTime);
	void MoveTowards(Vector2 destination, float deltaTime);
	virtual void Attack();
	void FacePlayer();
	float DistanceToPlayer();

	EnemyState state;
	Player* player;
	bool isFrozen;
	float freezeTimer = 0, freezeTime;

};
#endif