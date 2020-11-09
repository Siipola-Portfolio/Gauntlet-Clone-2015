#include "Food.h"

Food::Food(Camera* camera, const char* filepath, TileState state, int rowPosition, int columnPosition, int maxRows) :
	Tile(camera, filepath, state, rowPosition, columnPosition, maxRows),
	isTaken(false),
	nutrition(30)
{ }

Food::~Food() { }

void Food::Update(float deltaTime)
{
	Tile::Update(deltaTime);
}

void Food::ResolveCollision(Player* player)
{
	if (!isTaken)
	{
		isTaken = true;
		player->AddHealth(nutrition);
		filepath = "../resources/images/Floor.png";
		AddSprite();
		state = EMPTY;
	}
}