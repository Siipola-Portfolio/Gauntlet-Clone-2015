#ifndef GUI_H
#define GUI_H
#include <Application.h>
#include "GeneralManager.h"
#include "Camera.h"
#include "SoundSystem.h"
class GUI
{
public:
	GUI(Camera* camera, GeneralManager* generalManager, SoundSystem* soundSystem, int width, int screenWidth, int screenHeight);
	virtual ~GUI();

	void Update(float deltaTime);
	void Draw();

private:
	void WriteHealth(NHTV::Application& app, Vector2 position);
	void WriteClass(NHTV::Application& app, Vector2 position);
	void WriteFloor(NHTV::Application& app, Vector2 position);
	void WriteInventory(NHTV::Application& app, Vector2 position);

	NHTV::Rect GetCoords(bool isMuted);

	Camera* camera;
	GeneralManager* manager;
	SoundSystem* soundSystem;

	unsigned int spriteHandle, muteSpriteHandle;
	int width, screenWidth, screenHeight;
	NHTV::Rect muteCoords;
};
#endif