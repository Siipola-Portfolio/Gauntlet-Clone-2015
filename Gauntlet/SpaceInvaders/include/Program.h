#ifndef __Tutorial1_H_
#define __Tutorial1_H_

#include <Application.h>
#include <SpriteBatch.h>
#include "MainMenu.h"
#include "Game.h"
#include "GameOver.h"
#include "Victory.h"

// Derived application class that wraps up all globals neatly
class Program : public NHTV::Application
{
public:
	Program();
	virtual ~Program();

protected:
	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

private:
	void MenuUpdate(float deltaTime);
	void StartGame(PlayerChoise character);
	GameState state;
	MainMenu* menu;
	Game* game;
	GameOver* gameOver;
	Victory* victory;
    int screenWidth, screenHeight;
};

#endif // __Tutorial1_H_