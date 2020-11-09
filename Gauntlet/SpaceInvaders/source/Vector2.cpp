#include "Vector2.h"
#include <math.h>
Vector2::Vector2() { }

Vector2::Vector2(float x, float y) :
	x(x), y(y)
{ }

float Vector2::CalculateDistance()
{
	return sqrtf(x*x + y*y);
}

Vector2 Vector2::UnitVector()
{
	Vector2 result;
	float magnitude = CalculateDistance();
	if (magnitude != 0)
	{
		result.x = this->x / magnitude;
		result.y = this->y / magnitude;
		return result;
	}
	return *this;
}

Vector2 Vector2::operator+(Vector2 vectorToAdd)
{
	Vector2 result;
	result.x = this->x + vectorToAdd.x;
	result.y = this->y + vectorToAdd.y;
	return result;
}

Vector2 Vector2::operator-(Vector2 vectorToSubstract)
{
	Vector2 result;
	result.x = this->x - vectorToSubstract.x;
	result.y = this->y - vectorToSubstract.y;
	return result;
}

Vector2 Vector2::operator-()
{
	Vector2 result;
	result.x = -this->x;
	result.y = -this->y;
	return result;
}

Vector2 Vector2::operator*(float multiplier)
{
	Vector2 result;
	result.x = this->x * multiplier;
	result.y = this->y * multiplier;
	return result;
}