#include <random>
#include <cmath>
#include <chrono>

#include "utils.h"

int Utils::getRandomNumber(int from, int to)
{
	std::uniform_int_distribution<> dis(from, to);
	std::mt19937 rnd((unsigned int) std::chrono::steady_clock::now().time_since_epoch().count());
	return dis(rnd);
}

Utils::Vector2f::Vector2f() : x(0.0f), y(0.0f) {}
Utils::Vector2f::Vector2f(float x, float y) : x(x), y(y) {}

Utils::Vector2f::Vector2f(const Vector2f& vector) : x(vector.x), y(vector.y) {}

Utils::Vector2f& Utils::Vector2f::operator=(const Vector2f& vector)
{
	x = vector.x;
	y = vector.y;

	return *this;
}

Utils::Vector2f Utils::Vector2f::operator*(const float& num) const
{
	return Utils::Vector2f(num * x, num * y);
}

Utils::Vector2f Utils::Vector2f::operator+(const Vector2f& vector) const
{
	return Utils::Vector2f(vector.x + x, vector.y + y);
}

float Utils::Vector2f::distance(Vector2f vector1, Vector2f vector2)
{
	float dx = vector2.x - vector1.x;
	float dy = vector2.y - vector1.y;
	return sqrt(dx * dx + dy * dy);
}

float Utils::Vector2f::distanceSqr(Vector2f vector1, Vector2f vector2)
{
	float dx = vector2.x - vector1.x;
	float dy = vector2.y - vector1.y;
	return dx * dx + dy * dy;
}

Utils::Vector2f Utils::Vector2f::direction(Vector2f vector1, Vector2f vector2)
{
	return Utils::Vector2f(vector2.x - vector1.x, vector2.y - vector1.y);
}

void Utils::Vector2f::normalize()
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

float Utils::Vector2f::getLength()
{
	return sqrt(x * x + y * y);
}
