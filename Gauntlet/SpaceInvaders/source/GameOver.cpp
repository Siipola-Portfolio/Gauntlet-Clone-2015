#include "GameOver.h"
#include <Application.h>
GameOver::GameOver() { }

GameOver::~GameOver() { }

bool GameOver::Update(float deltaTime)
{
	NHTV::Application& app = NHTV::Application::GetInstance();
	return !app.IsKeyDown(NHTV::Keys::ESCAPE);
}

void GameOver::Draw()
{
	NHTV::Application& app = NHTV::Application::GetInstance();
	app.SetFont("../resources/fonts/invaders.fnt");
	app.DrawString("GAME OVER", 400, 500);
	app.DrawString("PRESS ESC TO QUIT", 400, 450);
}