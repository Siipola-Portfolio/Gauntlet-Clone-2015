#ifndef CAMERA_H
#define CAMERA_H
#include "Vector2.h"
class Camera
{
public:
	Camera(int screenWidth, int screenHeight, int GUIWidth, float velocity);
	virtual ~Camera();
	void Update(float deltaTime);
	Vector2 GetCameraPosition();
	void SetDestination(Vector2 destination);
	void GetCameraSize(int& width, int& height);
	void GiveWorldSize(int width, int height);
private:
	void ClampCamera();
	Vector2 position, destination;
	int worldWidth, worldHeight;
	const int SCREEN_WIDTH, SCREEN_HEIGHT, GUI_WIDTH;
	float velocity;
};

#endif