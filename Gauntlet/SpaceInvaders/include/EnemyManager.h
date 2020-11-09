#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include <Enemy.h>
class EnemyManager
{
public:
	EnemyManager();
	virtual ~EnemyManager();

	void Update(float deltaTime);
	void LateUpdate(float deltaTime);
	void Draw();

	void AddEnemy(Enemy* enemy);
	void CleanUpDeadEnemies();
	void ClearAllEnemies();
	std::vector<Enemy*> GetEnemies();
	std::vector<Projectile*> GetProjectiles();
	void AddProjectiles(std::vector<Projectile*> projectiles);
	void FreezeEnemies(float time);
private:
	std::vector<Enemy*> enemies;
	std::vector<Projectile*> enemyProjectiles;
};
#endif