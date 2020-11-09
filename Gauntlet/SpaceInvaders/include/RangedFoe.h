#ifndef RANGED_FOE
#define RANGED_FOE

#include "Enemy.h"

class RangedFoe : public Enemy
{
public:
	RangedFoe(Camera* camera, Player* player, SoundSystem* soundSystem);
	virtual ~RangedFoe();
	virtual void PostInitialize();

	virtual void Update(float deltaTime);
	virtual void UpdateMovement(float deltaTime);
	virtual void UpdateAttacking(float deltaTime);
	virtual void ProjectileHit(Projectile* projectile);

	std::vector<Projectile*> GetProjectiles();

protected:
	virtual void Attack();
	Projectile* GetFreeProjectile();
	std::vector<Projectile*> projectiles;

};
#endif