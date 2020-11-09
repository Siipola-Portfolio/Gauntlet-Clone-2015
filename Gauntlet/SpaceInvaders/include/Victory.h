#ifndef VICTORY_H
#define VICTORY_H

class Victory
{
public:
	Victory();
	virtual ~Victory();

	//returning true allows the application to exit
	bool Update(float deltaTime);
	void Draw();
};
#endif