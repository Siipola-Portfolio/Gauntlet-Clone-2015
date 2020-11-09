#ifndef DOOR_H
#define DOOR_H

#include "Tile.h"

class Door : public Tile
{
public:
	Door(Camera* camera, const char* filepath, TileState state, int rowPosition, int columnPosition, int maxRows);
	virtual ~Door();

	virtual void ResolveCollision(Player* player);

private:
	bool isOpened;
};
#endif