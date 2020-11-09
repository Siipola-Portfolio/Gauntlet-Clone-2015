#include "Game.h"
#include <iostream>
Game::Game(int screenWidth, int screenHeight, PlayerChoise character) :
	GUIWidth(256),
	screenWidth(screenWidth),
	screenHeight(screenHeight),
	state(GAME)
{
	soundSystem = new SoundSystem();

	camera = new Camera(screenWidth, screenHeight, GUIWidth, 100);
	int worldWidth, worldHeight;

	enemyManager = new EnemyManager();
	switch (character)
	{
	case WARRIOR: player = new Warrior(camera, soundSystem); break;
	case THIEF: player = new Thief(camera, soundSystem); break;
	case MAGE: player = new Mage(camera, soundSystem, enemyManager); break;
	case CLERIC: player = new Cleric(camera, soundSystem); break;
	}
	map = new Map(camera, player, enemyManager, soundSystem);
	map->GetWorldSize(worldWidth, worldHeight);
	camera->GiveWorldSize(worldWidth, worldHeight);

	manager = new GeneralManager(player, map, character);
	gui = new GUI(camera, manager, soundSystem, GUIWidth, screenWidth, screenHeight);
	collisionManager = new CollisionManager(map, player, enemyManager);
}

Game::~Game() { }

GameState Game::Update(float deltaTime)
{
	player->Update(deltaTime);
	collisionManager->UpdatePlayerCollisions(deltaTime);
	enemyManager->Update(deltaTime);
	collisionManager->UpdateEnemyCollisions(deltaTime);
	enemyManager->CleanUpDeadEnemies();
	map->Update(deltaTime);
	manager->Update(deltaTime);
	gui->Update(deltaTime);
	camera->Update(deltaTime);

	LateUpdate(deltaTime);

	if (map->HasPlayerWon())
		state = VICTORY;
	if (!player->GetAlive())
		state = GAME_OVER;

	return state;
}

void Game::LateUpdate(float deltaTime)
{
	map->LateUpdate(deltaTime);
	player->LateUpdate(deltaTime);
	enemyManager->LateUpdate(deltaTime);
}

void Game::Draw()
{
	map->Draw();
	player->Draw();
	enemyManager->Draw();
	gui->Draw();
}