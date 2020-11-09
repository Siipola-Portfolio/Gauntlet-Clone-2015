#include "ExitPortal.h"
#include <iostream>

ExitPortal::ExitPortal(Camera* camera, const char* filepath, TileState state, int rowPosition, int columnPosition, int maxRows) :
	Tile(camera, filepath, state, rowPosition, columnPosition, maxRows),
	isActivated(false)
{ }

ExitPortal::~ExitPortal() { }

void ExitPortal::ResolveCollision(Player* player)
{
	isActivated = true;
}

bool ExitPortal::IsActivated()
{
	return isActivated;
}