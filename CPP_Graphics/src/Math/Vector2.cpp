#include "Vector2.h"
#include <math.h>

namespace Math
{
	Vector2f::Vector2f() : x(0.0f), y(0.0f) {}
	Vector2f::Vector2f(float x, float y) : x(x), y(y) {}

	Vector2f::Vector2f(const Vector2f& vector) : x(vector.x), y(vector.y) {}

	Vector2f& Vector2f::operator=(const Vector2f& vector)
	{
		x = vector.x;
		y = vector.y;
		return *this;
	}

	Vector2f Vector2f::operator*(float num) const
	{
		return Vector2f(num * x, num * y);
	}

	Vector2f Vector2f::operator/(float num) const
	{
		return Vector2f(x / num, y / num);
	}

	Vector2f Vector2f::operator+(const Vector2f& vector) const
	{
		return Vector2f(vector.x + x, vector.y + y);
	}

	Vector2f Vector2f::operator-(const Vector2f& vector) const
	{
		return Vector2f(vector.x - x, vector.y - y);
	}

	Vector2f Vector2f::operator-() const
	{
		return Vector2f(-x, -y);
	}

	float Vector2f::dot(const Vector2f& vector1, const Vector2f& vector2)
	{
		return vector1.x * vector2.x + vector1.y * vector2.y;
	}

	float Vector2f::distance(const Vector2f& vector1, const Vector2f& vector2)
	{
		float dx = vector2.x - vector1.x;
		float dy = vector2.y - vector1.y;
		return sqrt(dx * dx + dy * dy);
	}

	float Vector2f::distanceSqr(const Vector2f& vector1, const Vector2f& vector2)
	{
		float dx = vector2.x - vector1.x;
		float dy = vector2.y - vector1.y;
		return dx * dx + dy * dy;
	}

	void Vector2f::normalize()
	{
		float length = getLength();
		if (length == 0)
		{
			x = 0.0f;
			y = 0.0f;
		}
		else
		{
			x /= length;
			y /= length;
		}
	}

	float Vector2f::getLength() const
	{
		return sqrt(x * x + y * y);
	}
}