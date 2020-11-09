#ifndef GAME_H
#define GAME_H

#include "SoundSystem.h"
#include "Camera.h"
#include "Map.h"
#include "GeneralManager.h"
#include "GUI.h"
#include "EnemyManager.h"
#include "CollisionManager.h"
#include "PlayerChoise.h"
#include "Warrior.h"
#include "Thief.h"
#include "Mage.h"
#include "Cleric.h"
#include "MainMenu.h"

class Game
{
public:
	Game(int screenWidth, int screenHeight, PlayerChoise character);
	virtual ~Game();
	GameState Update(float deltaTime);
	void LateUpdate(float deltaTime); //Placement of sprites
	void Draw();
private:
	//handles
	SoundSystem* soundSystem;
	Camera* camera;
	Map* map;
	GeneralManager* manager;
	GUI* gui;
	Player* player;
	EnemyManager* enemyManager;
	CollisionManager* collisionManager;

	//attributes
	int GUIWidth, screenWidth, screenHeight;
	GameState state;
};

#endif