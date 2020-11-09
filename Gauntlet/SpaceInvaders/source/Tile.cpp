#include "Tile.h"
#include <iostream>
Tile::Tile(Camera* camera, const char* filepath, TileState state, int rowPosition, int columnPosition, int maxRows) :
	Entity(camera),
	state(state),
	MAX_ROWS(maxRows),
	gridX(columnPosition),
	gridY(rowPosition)
{
	this->filepath = filepath;
	width = height = 32;
	AddSprite();
	position.x = (columnPosition + 0.5f)* width;
	position.y = (rowPosition + 0.5f) * height;
	occupant = nullptr;
}

Tile::~Tile() { }

void Tile::ResolveCollision(Character* character)
{
	if (state == EMPTY)
		return;
	else if (state == OCCUPIED && occupant == character)
		return;

	Vector2 charPos = character->GetPosition();
	Vector2 intersection = CalculateIntersection(character);

	//Resolve smaller intersection
	if (intersection.x != 0 || intersection.y != 0)
	{
		if (glm::abs(intersection.x) < glm::abs(intersection.y))
			charPos.x += intersection.x;
		else charPos.y += intersection.y;

		character->SetPosition(charPos);
	}
}

void Tile::ResolveCollision(Player* player)
{
	if (state == EMPTY)
		return;
	else if (state == OCCUPIED && occupant == player)
		return;

	Vector2 charPos = player->GetPosition();
	Vector2 intersection = CalculateIntersection(player);

	//Resolve smaller intersection
	if (intersection.x != 0 || intersection.y != 0)
	{
		if (glm::abs(intersection.x) < glm::abs(intersection.y))
			charPos.x += intersection.x;
		else charPos.y += intersection.y;

		player->SetPosition(charPos);
	}
}

void Tile::ResolveCollision(Projectile* projectile)
{
	if (state == WALL)
		projectile->SetAlive(false);
}

Vector2 Tile::CalculateIntersection(Entity* entity)
{
	float entityWidth, entityHeight;
	Vector2 entityPos = entity->GetPosition();
	entity->GetSize(entityWidth, entityHeight);

	//How far is entity from tile in x and y coorinates
	float minDistanceX = entityWidth*0.5f + width*0.5f;
	float minDistanceY = entityWidth*0.5f + height*0.5f;
	Vector2 distance = entityPos - position;
	Vector2 minDistance(minDistanceX, minDistanceY);

	//See how much they overlap on X and Y axis
	Vector2 intersection(0, 0);

	if (glm::abs(distance.x) < minDistance.x)
	{
		if (distance.x > 0)
			intersection.x = minDistance.x - distance.x;
		else intersection.x = -minDistance.x - distance.x;
	}
	if (glm::abs(distance.y) < minDistance.y)
	{
		if (distance.y > 0)
			intersection.y = minDistanceY - distance.y;
		else intersection.y = -minDistanceY - distance.y;
	}
	return intersection;
}

void Tile::Occupy(Character* character)
{
	occupant = character;
	state = OCCUPIED;
}

void Tile::Empty()
{
	occupant = nullptr;
	state = EMPTY;
}

void Tile::GetGridPosition(int&x, int& y)
{
	x = gridX;
	y = gridY;
}

bool Tile::IsPassable()
{
	return !(state == WALL);
}

bool Tile::IsOccupied()
{
	return (state == OCCUPIED);
}

Character* Tile::GetOccupant()
{
	return occupant;
}