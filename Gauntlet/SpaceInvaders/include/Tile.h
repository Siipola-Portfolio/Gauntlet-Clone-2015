#ifndef TILE_H
#define TILE_H

#include "Character.h"
#include "Player.h"

enum TileState
{
	EMPTY,
	OCCUPIED,
	WALL
};

class Tile : public Entity
{
public:
	Tile(Camera* camera, const char* filepath, TileState state, int rowPosition, int columnPosition, int maxRows);
	virtual ~Tile();

	virtual void ResolveCollision(Character* character);
	virtual void ResolveCollision(Projectile* projectle);
	virtual void ResolveCollision(Player* player);
	void Occupy(Character* character);
	void Empty();

	void GetGridPosition(int& x, int& y);
	bool IsPassable();
	bool IsOccupied();
	Character* GetOccupant();
protected:
	Vector2 CalculateIntersection(Entity* entity);

	int gridX, gridY;
	const int MAX_ROWS;
	TileState state;
	Character* occupant;
};
#endif