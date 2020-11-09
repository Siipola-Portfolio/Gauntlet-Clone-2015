#include "EnemyManager.h"
#include <iostream>
#include <algorithm>

EnemyManager::EnemyManager() { }

EnemyManager::~EnemyManager()
{
	ClearAllEnemies();
}

void EnemyManager::Update(float deltaTime)
{
	for (Enemy* enemy : enemies)
		enemy->Update(deltaTime);

	std::vector<Projectile*> toRemove;
	for (Projectile* projectile : enemyProjectiles)
	{
		projectile->Update(deltaTime);
		if (projectile->CanBeRemoved() && !projectile->GetAlive())
			toRemove.push_back(projectile);
	}
	for (Projectile* projectile : toRemove)
	{
		enemyProjectiles.erase(std::remove(enemyProjectiles.begin(), enemyProjectiles.end(), projectile), enemyProjectiles.end());
		delete projectile;
	}
}

void EnemyManager::LateUpdate(float deltaTime)
{
	for (Enemy* enemy : enemies)
		enemy->LateUpdate(deltaTime);

	for (Projectile* projectile : enemyProjectiles)
		projectile->LateUpdate(deltaTime);

	CleanUpDeadEnemies();
}

void EnemyManager::Draw()
{
	for (Enemy* enemy : enemies)
		enemy->Draw();

	for (Projectile* projectile : enemyProjectiles)
		projectile->Draw();
}

void EnemyManager::AddEnemy(Enemy* enemy)
{
	enemies.push_back(enemy);
}

void EnemyManager::AddProjectiles(std::vector<Projectile*> projectiles)
{
	for (Projectile* projectile : projectiles)
		if (projectile != NULL)
			enemyProjectiles.push_back(projectile);
}

void EnemyManager::FreezeEnemies(float time)
{
	for (Enemy* enemy : enemies)
		enemy->Freeze(time);
}

void EnemyManager::CleanUpDeadEnemies()
{
	std::vector<Enemy*> deadEnemies;
	for (Enemy* enemy : enemies)
		if (!enemy->GetAlive())
			deadEnemies.push_back(enemy);

	for (Enemy* enemy : deadEnemies)
	{
		enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
		delete enemy;
	}
}

void EnemyManager::ClearAllEnemies()
{
	for (Enemy* enemy : enemies)
		delete enemy;
	enemies.clear();

	for (Projectile* projectile : enemyProjectiles)
		delete projectile;
	enemyProjectiles.clear();
}

std::vector<Enemy*> EnemyManager::GetEnemies() { return enemies; }

std::vector<Projectile*> EnemyManager::GetProjectiles() { return enemyProjectiles; }