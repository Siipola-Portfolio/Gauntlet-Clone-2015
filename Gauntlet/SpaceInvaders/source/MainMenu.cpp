#include <Application.h>
#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu(int screenWidth, int screenHeight) :
	screenWidth(screenWidth), screenHeight(screenHeight)
{ }

MainMenu::~MainMenu() { }

void MainMenu::Update(float deltaTime) { }

void MainMenu::Draw()
{
	NHTV::Application& app = NHTV::Application::GetInstance();
	app.SetFont("../resources/fonts/invaders.fnt");
	app.DrawString("PRESS 1 FOR WARRIOR", 300, 500, 1);
	app.DrawString("PRESS 2 FOR THIEF", 300, 450, 1);
	app.DrawString("PRESS 3 FOR MAGE", 300, 400, 1);
	app.DrawString("PRESS 4 FOR CLERIC", 300, 350, 1);
	app.DrawString("PRESS ESC TO QUIT", 300, 300, 1);
	app.DrawString("Use ArrowKeys to Move", 900, 700, 0.8f);
	app.DrawString("Spacebar to shoot", 900, 670, 0.8f);
	app.DrawString("LCtrl to use a potion", 900, 640, 0.8f);
	app.DrawString("M to toggle mute", 900, 610, 0.8f);
}

PlayerChoise MainMenu::StartGame()
{
	NHTV::Application& app = NHTV::Application::GetInstance();
	if (app.IsKeyDown(NHTV::Keys::D1))
		return WARRIOR;
	else if (app.IsKeyDown(NHTV::Keys::D2))
		return THIEF;
	if (app.IsKeyDown(NHTV::Keys::D3))
		return MAGE;
	if (app.IsKeyDown(NHTV::Keys::D4))
		return CLERIC;
	else if (app.IsKeyDown(NHTV::Keys::ESCAPE))
		return QUIT;
	else return NONE;
}