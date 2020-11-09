#ifndef POTION_H
#define POTION_H

#include "Tile.h"

class Potion : public Tile
{
public:
	Potion(Camera* camera, const char* filepath, TileState state, int rowPosition, int columnPosition, int maxRows);
	~Potion();

	virtual void Update(float deltaTime);

	virtual void ResolveCollision(Player* player);

private:
	bool isTaken;
};
#endif