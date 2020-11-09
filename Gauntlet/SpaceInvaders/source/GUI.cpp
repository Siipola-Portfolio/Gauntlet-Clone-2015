#include "GUI.h"
#include <SpriteManager.h>
#include <string>

GUI::GUI(Camera* camera, GeneralManager* manager, SoundSystem* soundSystem, int width, int screenWidth, int screenHeight) :
	camera(camera),
	manager(manager),
	soundSystem(soundSystem),
	screenWidth(screenWidth),
	screenHeight(screenHeight)
{
	NHTV::SpriteManager* spriteManager = NHTV::SpriteManager::GetInstance();
	if (spriteManager)
	{
		spriteHandle = spriteManager->AddSprite("../resources/images/GUI.png", glm::vec2(width, screenHeight), glm::vec2(0, 0), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec4(1, 1, 1, 1));
		spriteManager->MoveSprite(spriteHandle, screenWidth - width, 0);
		muteCoords = GetCoords(false);
		muteSpriteHandle = spriteManager->AddSprite("../resources/images/Mute.png", glm::vec2(60, 60), glm::vec2(0, 0), muteCoords, glm::vec4(1, 1, 1, 1));
		spriteManager->MoveSprite(muteSpriteHandle, 1050, 100);
	}
}

GUI::~GUI() { }

void GUI::Update(float deltaTime) { }

void GUI::Draw()
{
	NHTV::SpriteManager* spriteManager = NHTV::SpriteManager::GetInstance();
	if (spriteManager)
	{
		spriteManager->MarkSpriteForDraw(spriteHandle);
		spriteManager->SetSpriteUVCoordinates(muteSpriteHandle, GetCoords(soundSystem->IsMuted()));
		spriteManager->MarkSpriteForDraw(muteSpriteHandle);
	}

	NHTV::Application& app = NHTV::Application::GetInstance();
	app.SetFont("../resources/fonts/arial.fnt");
	WriteFloor(app, Vector2(1050, 550));
	WriteClass(app, Vector2(1050, 700));
	WriteHealth(app, Vector2(1050, 650));
	WriteInventory(app, Vector2(1050, 450));
}

void GUI::WriteHealth(NHTV::Application& app, Vector2 position)
{
	std::string healthStr = "Health: ";
	healthStr.append(std::to_string(manager->GetHealth()));
	char const* health = healthStr.c_str();

	app.DrawString(health, static_cast<int>(glm::round(position.x)), static_cast<int>(glm::round(position.y)));
}

void GUI::WriteClass(NHTV::Application& app, Vector2 position)
{ app.DrawString(manager->GetClass(), static_cast<int>(glm::round(position.x)), static_cast<int>(glm::round(position.y))); }

void GUI::WriteFloor(NHTV::Application& app, Vector2 position)
{
	std::string floorStr = "Floor: ";
	floorStr.append(std::to_string(manager->GetFloor()));
	char const* floor = floorStr.c_str();
	app.DrawString(floor, static_cast<int>(glm::round(position.x)), static_cast<int>(glm::round(position.y)));
}

void GUI::WriteInventory(NHTV::Application& app, Vector2 position)
{
	int numberOfKeys = 0;
	int numberOfPotions = 0;
	manager->GetInventory(numberOfKeys, numberOfPotions);
	if (numberOfKeys > 0)
	{
		std::string keysStr = "Keys: ";
		keysStr.append(std::to_string(numberOfKeys));
		char const* keys = keysStr.c_str();

		app.DrawString(keys, static_cast<int>(glm::round(position.x)), static_cast<int>(glm::round(position.y)));
	}
	if (numberOfPotions > 0)
	{
		std::string keysStr = "Potions: ";
		keysStr.append(std::to_string(numberOfPotions));
		char const* keys = keysStr.c_str();

		app.DrawString(keys, static_cast<int>(glm::round(position.x)), static_cast<int>(glm::round(position.y)) - 50);
	}
}

NHTV::Rect GUI::GetCoords(bool isMuted)
{
	NHTV::Rect coords;
	if (isMuted)
		coords = { 60, 0, 60, 60 };
	else
		coords = { 0, 0, 60, 60 };

	return coords;
}