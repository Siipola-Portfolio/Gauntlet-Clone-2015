#include "Program.h"

#define USE_ENEMY_SPRITE_BATCH 1

APPLICATION_ENTRY(Program);

using namespace NHTV;

Program::Program() { }

Program::~Program() { }

bool Program::onCreate(int a_argc, char* a_argv[])
{
	setBackgroundColor(NHTV::SColour(0x00, 0x00, 0x00, 0xFF));
	AddFont("../resources/fonts/invaders.fnt");
	GetScreenSize(screenWidth, screenHeight);

	menu = new MainMenu(screenWidth, screenHeight);
	gameOver = new GameOver();
	victory = new Victory();
	state = MAIN_MENU;

	return true;
}

void Program::onUpdate(float deltaTime)
{

	switch (state)
	{
	case MAIN_MENU: MenuUpdate(deltaTime); break;
	case GAME: 	state = game->Update(deltaTime); break;
	case GAME_OVER:
		if (!gameOver->Update(deltaTime))
			destroy();
		break;
	case VICTORY:
		if (victory->Update(deltaTime))
			destroy();
		break;
	}
}

void Program::MenuUpdate(float deltaTime)
{
	menu->Update(deltaTime);
	PlayerChoise input;
	input = menu->StartGame();
	switch (input)
	{
	case QUIT:
		destroy();
		break;
	case NONE:
		break;
	case WARRIOR:
		StartGame(WARRIOR);
		state = GAME;
		break;
	case THIEF:
		StartGame(THIEF);
		state = GAME;
		break;
	case MAGE:
		StartGame(MAGE);
		state = GAME;
		break;
	case CLERIC:
		StartGame(CLERIC);
		state = GAME;
		break;
	}
}

void Program::onDraw()
{
	clearScreen();
	float fDeltaT = GetDeltaTime();

	switch (state)
	{
	case MAIN_MENU: menu->Draw(); break;
	case GAME: game->Draw(); break;
	case GAME_OVER: gameOver->Draw(); break;
	case VICTORY: victory->Draw(); break;
	}
}

void Program::onDestroy()
{
	delete menu;
	menu = nullptr;
	delete victory;
	victory = nullptr;
	delete gameOver;
	gameOver = nullptr;
}

void Program::StartGame(PlayerChoise character) { game = new Game(screenWidth, screenHeight, character); }