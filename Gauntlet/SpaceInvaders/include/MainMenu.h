#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "PlayerChoise.h"
enum GameState
{
	MAIN_MENU,
	GAME,
	PAUSED,
	VICTORY,
	GAME_OVER
};

class MainMenu
{
public:
	MainMenu(int screenWidth, int screenHeight);
	virtual ~MainMenu();

	void Update(float deltaTime);
	void Draw();
	PlayerChoise StartGame();

private:
	int screenWidth, screenHeight;
};
#endif