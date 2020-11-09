#include "Potion.h"

Potion::Potion(Camera* camera, const char* filepath, TileState state, int rowPosition, int columnPosition, int maxRows) :
	Tile(camera, filepath, state, rowPosition, columnPosition, maxRows),
	isTaken(false)
{ }

Potion::~Potion() { }

void Potion::Update(float deltaTime)
{
	Tile::Update(deltaTime);
}

void Potion::ResolveCollision(Player* player)
{
	if (!isTaken)
	{
		isTaken = true;
		player->AddItem(POTION);
		filepath = "../resources/images/Floor.png";
		AddSprite();
		state = EMPTY;
	}
}