#ifndef EXIT_PORTAL_H
#define EXIT_PORTAL_H
#include "Tile.h"

class ExitPortal : public Tile
{
public:
	ExitPortal(Camera* camera, const char* filepath, TileState state, int rowPosition, int columnPosition, int maxRows);
	virtual ~ExitPortal();
	virtual void ResolveCollision(Player* player);

	bool IsActivated();
private:
	bool isActivated;
};
#endif