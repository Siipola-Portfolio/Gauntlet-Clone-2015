#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include "Projectile.h"
#include "SoundSystem.h"
enum Facing
{
	UP,
	UPRIGHT,
	RIGHT,
	DOWNRIGHT,
	DOWN,
	DOWNLEFT,
	LEFT,
	UPLEFT
};

class Character : public Entity
{
public:
	Character(Camera* camera, SoundSystem* soundSystem);
	virtual ~Character();
	virtual void PostInitialize();

	virtual void Update(float deltaTime);
	virtual void LateUpdate(float deltaTime);
	virtual void Draw();
	
	void ResetPreviousPosition();
	virtual void ProjectileHit(Projectile* projectile);
	virtual void TakeDamage(int amount);
	virtual void Die();
	void AddHealth(int amount);
	int GetHealth();
	bool IsMoving();
	Vector2 GetPreviousPosition();

protected:
	void Move(Vector2 movement);
	void Shoot(Projectile* projectile);
	void Shoot(Projectile* projectile, Vector2 direction);
	virtual void InitializeUVCoords();
	void SetFacing(Vector2 dir);
	NHTV::Rect GetCorrectUVCoords();

	SoundSystem* soundSystem;
	Vector2 topLeftCoords;
	int health, damage, armor;
	int animationState = 0;
	float velocity, range, firerate, fireTimer = 0, animationRate, animationTimer = 0;
	NHTV::Rect uvCoords[4][4];


private:
	Vector2 previousPosition;
	Facing facing;
	bool isMoving;
	int spriteDirection = 0;
};
#endif