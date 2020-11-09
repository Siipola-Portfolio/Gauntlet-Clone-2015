#ifndef KEY_H
#define KEY_H

#include "Tile.h"

class Key : public Tile
{
public:
	Key(Camera* camera, const char* filepath, TileState state, int rowPosition, int columnPosition, int maxRows);
	virtual ~Key();

	virtual void ResolveCollision(Player* player);

private:
	bool isTaken;
};
#endif
