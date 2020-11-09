#include "Camera.h"
#include <Application.h>
#include <assert.h>

Camera::Camera(int screenWidth, int screenHeight, int GUIWidth, float velocity) :
	position(0, 0), destination(0, 0),
	SCREEN_WIDTH(screenWidth), SCREEN_HEIGHT(screenHeight),
	worldWidth(0), worldHeight(0),
	GUI_WIDTH(GUIWidth),
	velocity(velocity)
{ }

Camera::~Camera() { }

void Camera::Update(float deltaTime)
{
	position = destination;
	ClampCamera();

}

void Camera::ClampCamera()
{
	assert(worldWidth != 0);
	if (position.x < 0)
		position.x = 0;
	else if (position.x > static_cast<float>((worldWidth - SCREEN_WIDTH + GUI_WIDTH)))
		position.x = static_cast<float>((worldWidth - SCREEN_WIDTH + GUI_WIDTH));

	if (position.y < 0)
		position.y = 0;
	else if (position.y > static_cast<float>((worldHeight - SCREEN_HEIGHT)))
		position.y = static_cast<float>((worldHeight - SCREEN_HEIGHT));
}

void Camera::SetDestination(Vector2 destination)
{
	destination.x -= SCREEN_WIDTH * 0.5f;
	destination.x += GUI_WIDTH * 0.5f;
	destination.y -= SCREEN_HEIGHT * 0.5f;
	this->destination = destination;
}

Vector2 Camera::GetCameraPosition()
{
	return position;
}

void Camera::GetCameraSize(int&width, int& height)
{
	width = SCREEN_WIDTH - GUI_WIDTH;
	height = SCREEN_HEIGHT;
}

void Camera::GiveWorldSize(int width, int height)
{
	worldWidth = width;
	worldHeight = height;
}