#ifndef MELEE_FOE
#define MELEE_FOE

#include "Enemy.h"

class MeleeFoe : public Enemy
{
public:
	MeleeFoe(Camera* camera, Player* player, SoundSystem* soundSystem);
	virtual ~MeleeFoe();
	virtual void PostInitialize();

	virtual void Update(float deltaTime);
	virtual void ProjectileHit(Projectile* projectile);

private:
	virtual void Attack();
};
#endif