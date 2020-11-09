#ifndef MAP_H
#define MAP_H

#include <vector>
#include "Tile.h"
#include "Camera.h"
#include "MeleeFoeSpawner.h"
#include "RangedFoeSpawner.h"
#include "SpecialEnemySpawner.h"
#include "ExitPortal.h"
#include "Key.h"
#include "Door.h"
#include "Food.h"
#include "Potion.h"
class Map
{
public:
	Map(Camera* camera, Player* player, EnemyManager* enemyManager, SoundSystem* soundSystem);
	virtual ~Map();
	void Update(float deltaTime);
	void LateUpdate(float deltaTime);
	void Draw();

	void LoadNextLevel();
	bool HasPlayerWon();

	void GetWorldSize(int& width, int& height);
	int GetCurrentLevel();
	Tile* GetTile(int x, int y);
	ExitPortal* GetExit();
	std::vector<Spawner*>* GetSpawners();

	const int TILE_ROWS = 41, TILE_COLUMNS = 41, TILE_SIZE = 32;

private:
	void ReadTileMap(const char* filepath);
	void CreateTile(char c, int row, int column);
	void DesignateSpawners();
	void EraseCurrentLevel();
	void GetTilesInScreen(int& minX, int& minY, int&maxX, int& maxY);
	std::vector<Tile*> DesignateRectangle(int bottomLeftX, int bottomLeftY, int width);

	Tile* playerSpawn;
	ExitPortal* exit;

	Tile* tilemap[41][41];
	std::vector<Spawner*> spawners;
	Camera* camera;
	Player* player;
	EnemyManager* enemyManager;
	SoundSystem* soundSystem;
	int currentLevel;
	const int TOTAL_LEVELS;
};
#endif