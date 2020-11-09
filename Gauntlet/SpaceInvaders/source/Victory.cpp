#include "Victory.h"
#include <Application.h>
Victory::Victory() { }

Victory::~Victory() { }

bool Victory::Update(float deltaTime)
{
	NHTV::Application& app = NHTV::Application::GetInstance();
	return app.IsKeyDown(NHTV::Keys::ESCAPE);
}

void Victory::Draw()
{
	NHTV::Application& app = NHTV::Application::GetInstance();
	app.SetFont("../resources/fonts/invaders.fnt");
	app.DrawString("YOU WON!", 400, 500);
	app.DrawString("PRESS ESC TO QUIT", 400, 450);
}