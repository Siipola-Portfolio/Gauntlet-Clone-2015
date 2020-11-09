#include "Key.h"

Key::Key(Camera* camera, const char* filepath, TileState state, int rowPosition, int columnPosition, int maxRows)
	: Tile(camera, filepath, state, rowPosition, columnPosition, maxRows),
	isTaken(false)
{ }

Key::~Key() { }

void Key::ResolveCollision(Player* player)
{
	if (!isTaken)
	{
		isTaken = true;
		player->AddItem(KEY);
		filepath = "../resources/images/Floor.png";
		AddSprite();
		state = EMPTY;
	}

	Tile::ResolveCollision(player);
}