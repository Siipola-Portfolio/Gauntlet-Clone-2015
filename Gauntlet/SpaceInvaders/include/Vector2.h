#ifndef VECTOR_2
#define VECTOR_2

struct Vector2
{
	Vector2();
	Vector2(float x, float y);

	float CalculateDistance();
	Vector2 UnitVector();

	Vector2 operator+(Vector2 vectorToAdd);
	Vector2 operator-(Vector2 vectorToSubtract);
	Vector2 operator-();
	Vector2 operator*(float multiplier);

	float x, y;

};
#endif