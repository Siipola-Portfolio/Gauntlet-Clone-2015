#ifndef GAME_OVER_H
#define GAME_OVER_H

class GameOver
{
public:
	GameOver();
	~GameOver();

	//if false is returned, application can exit
	bool Update(float deltaTime);
	void Draw();
};
#endif