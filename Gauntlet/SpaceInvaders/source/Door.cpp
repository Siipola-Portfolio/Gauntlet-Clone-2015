#include "Door.h"

Door::Door(Camera* camera, const char* filepath, TileState state, int rowPosition, int columnPosition, int maxRows) :
	Tile(camera, filepath, state, rowPosition, columnPosition, maxRows),
	isOpened(false)
{ }

Door::~Door() { }

void Door::ResolveCollision(Player* player)
{
	if (!isOpened)
	{
		if (player->UseKey())
		{
			isOpened = true;
			filepath = "../resources/images/Floor.png";
			AddSprite();
			state = EMPTY;
		}
	}

	Tile::ResolveCollision(player);
}