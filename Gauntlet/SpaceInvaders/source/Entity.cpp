#include "Entity.h"

Entity::Entity(Camera* camera) :
	camera(camera)
{
	isAlive = true;
}

Entity::~Entity() { }

void Entity::PostInitialize() { }

void Entity::AddSprite()
{
	NHTV::SpriteManager* spriteManager = NHTV::SpriteManager::GetInstance();
	if (spriteManager)
		spriteHandle = spriteManager->AddSprite(filepath, glm::vec2(width, height), glm::vec2(0.5f, 0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec4(1, 1, 1, 1));
}

void Entity::Update(float deltaTime) { }

void Entity::LateUpdate(float deltaTime)
{
	Vector2 cameraPosition = camera->GetCameraPosition();

	NHTV::SpriteManager* spriteManager = NHTV::SpriteManager::GetInstance();
	if (spriteManager)
		spriteManager->MoveSprite(spriteHandle, static_cast<int>(glm::round(position.x - cameraPosition.x)), static_cast<int>(glm::round(position.y - cameraPosition.y)));
}

void Entity::Draw()
{
	if (IsInScreen() && isAlive)
	{
		NHTV::SpriteManager* spriteManager = NHTV::SpriteManager::GetInstance();
		if (spriteManager)
			spriteManager->MarkSpriteForDraw(spriteHandle);
	}
}

void Entity::GetSize(float& width, float& height)
{
	width = this->width;
	height = this->height;
}

void Entity::SetSize(float width, float height)
{
	this->width = width;
	this->height = height;
}

bool Entity::IsInScreen()
{
	int screenWidth, screenHeight;
	Vector2 cameraPosition = camera->GetCameraPosition();
	camera->GetCameraSize(screenWidth, screenHeight);

	return !(position.x + width*0.5f < cameraPosition.x ||
		position.x - width*0.5f > cameraPosition.x + static_cast<float>(screenWidth) ||
		position.y + height*0.5f < cameraPosition.y ||
		position.y - height*0.5f > cameraPosition.y + static_cast<float>(screenHeight));
}

Vector2 Entity::GetPosition() { return position; }

void Entity::SetPosition(Vector2 position) { this->position = position; }

bool Entity::GetAlive() { return isAlive; }

void Entity::SetAlive(bool alive) { isAlive = alive; }