#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"

class Projectile : public Entity
{
public:
	Projectile(Camera* camera, int damage, float velocity, bool isPlayers);
	virtual ~Projectile();

	void Update(float deltaTime);
	void Shoot(Vector2 newPosition);
	virtual void Draw();
	bool IsPlayers();
	int GetDamage();
	void SetDirection(Vector2 direction);
	bool CanBeRemoved();
	void Delete();
private:
	bool isPlayers, canBeRemoved;
	int damage;
	float velocity, lifeTimer = 0;
	const float LIFE_TIME;
	Vector2 direction;
};
#endif