#ifndef FOOD_H
#define FOOD_H

#include "Tile.h"

class Food : public Tile
{
public:
	Food(Camera* camera, const char* filepath, TileState state, int rowPosition, int columnPosition, int maxRows);
	virtual ~Food();

	virtual void Update(float deltaTime);

	virtual void ResolveCollision(Player* player);

private:
	bool isTaken;
	int nutrition;
};
#endif