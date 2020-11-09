#ifndef ENTITY_H
#define ENTITY_H

#include <SpriteManager.h>
#include "Camera.h"
#include "Vector2.h"
class Entity
{
public:
	Entity(Camera* camera);
	virtual ~Entity();
	virtual void PostInitialize();

	virtual void Update(float deltaTime);
	virtual void LateUpdate(float deltaTime);
	virtual void Draw();

	Vector2 GetPosition();
	virtual void SetPosition(Vector2 position);

	void GetSize(float& width, float& height);
	void SetSize(float width, float height);

	bool GetAlive();
	void SetAlive(bool alive);
	bool IsInScreen();

protected:
	void AddSprite();

	const  char* filepath;
	bool isAlive;
	unsigned int spriteHandle;
	float width, height;
	Vector2 position;
	Camera* camera;
};
#endif