#include <fstream>
#include <iostream>
#include <string.h>
#include "Map.h"

Map::Map(Camera* camera, Player* player, EnemyManager* enemyManager, SoundSystem* soundSystem) :
	camera(camera),
	player(player),
	enemyManager(enemyManager),
	soundSystem(soundSystem),
	currentLevel(1),
	TOTAL_LEVELS(4)
{
	ReadTileMap("../resources/Level1.txt");
	DesignateSpawners();
}

Map::~Map() { }

void Map::Update(float deltaTime)
{
	for (Spawner* spawner : spawners)
		spawner->Update(deltaTime);

	if (exit->IsActivated())
	{
		soundSystem->PlayChangeLevel();
		LoadNextLevel();
	}
}

void Map::LateUpdate(float deltaTime)
{
	int minX, minY, maxX, maxY;
	GetTilesInScreen(minX, minY, maxX, maxY);

	for (int column = minX; column <= maxX; column++)
		for (int row = minY; row <= maxY; row++)
			tilemap[column][row]->LateUpdate(deltaTime);
}

void Map::Draw()
{
	int minX, minY, maxX, maxY;
	GetTilesInScreen(minX, minY, maxX, maxY);

	for (int column = minX; column <= maxX; column++)
		for (int row = minY; row <= maxY; row++)
			tilemap[column][row]->Draw();
}

void Map::ReadTileMap(const char* filepath)
{
	char* c;
	c = new char[TILE_COLUMNS + 1];
	std::ifstream textFile(filepath);
	int rows = TILE_ROWS - 1;
	if (textFile.is_open())
	{
		while (!textFile.eof() && rows >= 0)
		{
			textFile.getline(c, 1024);
			for (int i = TILE_COLUMNS - 1; i >= 0; i--)
				CreateTile(c[i], rows, i);
			rows--;
		}
	}

	player->SetPosition(playerSpawn->GetPosition());
	player->ResetPreviousPosition();
	camera->SetDestination(playerSpawn->GetPosition());
	//skipping next update from player due to too large deltaTime caused by Loading a whole level
	player->SkipNextUpdate();
	delete c;
}

void Map::CreateTile(char c, int row, int column)
{
	const char* empty = "../resources/images/Floor.png";
	const char* wall = "../resources/images/Wall.png";
	const char* meleeSpawner = "../resources/images/MeleeSpawner.png";
	const char* rangeSpawner = "../resources/images/RangeSpawner.png";
	const char* exitPortal = "../resources/images/Exit.png";
	const char* keyStr = "../resources/images/Key.png";
	const char* doorStr = "../resources/images/Door.png";
	const char* foodStr = "../resources/images/Food.png";
	const char* potionStr = "../resources/images/Potion.png";
	Tile* tile;
	Spawner* spawner;
	switch (c)
	{
	case '.': tilemap[column][row] = new Tile(camera, empty, EMPTY, row, column, TILE_ROWS); break;
	case '#': tilemap[column][row] = new Tile(camera, wall, WALL, row, column, TILE_ROWS); break;
	case 'K': tilemap[column][row] = new Key(camera, keyStr, WALL, row, column, TILE_ROWS); break;
	case 'D': tilemap[column][row] = new Door(camera, doorStr, WALL, row, column, TILE_ROWS); break;
	case 'F': tilemap[column][row] = new Food(camera, foodStr, WALL, row, column, TILE_ROWS); break;
	case 'P': tilemap[column][row] = new Potion(camera, potionStr, WALL, row, column, TILE_ROWS); break;
	case '0':
		playerSpawn = new Tile(camera, empty, EMPTY, row, column, TILE_ROWS);
		tilemap[column][row] = playerSpawn;
		break;
	case 'E':
		exit = new ExitPortal(camera, exitPortal, EMPTY, row, column, TILE_ROWS);
		tilemap[column][row] = exit;
		break;
	case 'M':
		spawner = new MeleeFoeSpawner(camera, meleeSpawner, WALL, row, column, TILE_ROWS, player, enemyManager, soundSystem);
		tilemap[column][row] = spawner;
		spawners.push_back(spawner);
		break;
	case 'R':
		spawner = new RangedFoeSpawner(camera, rangeSpawner, WALL, row, column, TILE_ROWS, player, enemyManager, soundSystem);
		tilemap[column][row] = spawner;
		spawners.push_back(spawner);
		break;
	case 'S':
		spawner = new SpecialEnemySpawner(camera, empty, EMPTY, row, column, TILE_ROWS, player, enemyManager, soundSystem, this);
		tilemap[column][row] = spawner;
		spawners.push_back(spawner);
		break;
	default:
		assert(false);
		tilemap[column][row] = new Tile(camera, empty, EMPTY, row, column, TILE_ROWS);
		break;
	}
}

void Map::LoadNextLevel()
{
	currentLevel++;
	if (currentLevel > TOTAL_LEVELS)
		return;

	//Create correct filepath by appendin the number of level and .txt to the base filepath
	char strLevel[32];
	sprintf(strLevel, "%d", currentLevel);
	char filepath[64] = "../resources/Level";
	strcat(filepath, strLevel);
	strcat(filepath, ".txt");
	std::cout << filepath << std::endl;

	EraseCurrentLevel();
	ReadTileMap(filepath);
	DesignateSpawners();
}

void Map::DesignateSpawners()
{
	for (Spawner* spawner : spawners)
	{
		int gridX, gridY;
		spawner->GetGridPosition(gridX, gridY);
		std::vector<Tile*> spawnArea = DesignateRectangle(gridX - 1, gridY - 1, 3);
		spawner->DesignateSpawnArea(spawnArea);
	}
}

std::vector<Tile*> Map::DesignateRectangle(int bottomLeftX, int bottomLeftY, int width)
{
	std::vector<Tile*> rectangle;
	for (int i = bottomLeftX; i < bottomLeftX + width; i++)
		for (int j = bottomLeftY; j < bottomLeftY + width; j++)
			rectangle.push_back(GetTile(i, j));

	return rectangle;
}

void Map::EraseCurrentLevel()
{
	for (int column = 0; column < TILE_COLUMNS; column++)
		for (int row = 0; row < TILE_ROWS; row++)
		{
			delete tilemap[column][row];
			tilemap[column][row] = nullptr;
		}

	spawners.clear();
	enemyManager->ClearAllEnemies();
}

Tile* Map::GetTile(int x, int y)
{
	assert(x < 0 || x >= TILE_COLUMNS || y < 0 || y <= TILE_ROWS);
	glm::clamp(x, 0, TILE_COLUMNS - 1);
	glm::clamp(y, 0, TILE_ROWS - 1);

	return tilemap[x][y];
}

void Map::GetWorldSize(int& width, int& height)
{
	width = TILE_COLUMNS * TILE_SIZE;
	height = TILE_ROWS * TILE_SIZE;
}

void Map::GetTilesInScreen(int& minX, int& minY, int& maxX, int& maxY)
{
	int camWidth, camHeight;
	Vector2 cameraPosition = camera->GetCameraPosition();
	camera->GetCameraSize(camWidth, camHeight);
	minX = static_cast<int>(glm::floor(cameraPosition.x / TILE_SIZE));
	minY = static_cast<int>(glm::floor(cameraPosition.y / TILE_SIZE));
	maxX = static_cast<int>(glm::ceil((cameraPosition.x + static_cast<float>(camWidth)) / TILE_SIZE));
	maxY = static_cast<int>(glm::ceil((cameraPosition.y + static_cast<float>(camHeight)) / TILE_SIZE));
	if (maxX > 40)
		maxX = 40;
	if (maxY > 40)
		maxY = 40;
}

bool Map::HasPlayerWon() { return (currentLevel > TOTAL_LEVELS); }

ExitPortal* Map::GetExit() { return exit; }

std::vector<Spawner*>* Map::GetSpawners() { return &spawners; }

int Map::GetCurrentLevel() { return currentLevel; }