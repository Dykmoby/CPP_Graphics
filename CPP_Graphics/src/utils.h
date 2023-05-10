#pragma once

static class Utils
{
public:
	static int getRandomNumber(int from, int to);

	class Vector2f {
	public:
		float x, y;

		Vector2f();
		Vector2f(float x, float y);

		Vector2f(const Vector2f& v);

		Vector2f& operator=(const Vector2f &vector);
		Vector2f operator*(const float &num) const;
		Vector2f operator+(const Vector2f &vector) const;

		static float distance(Vector2f vector1, Vector2f vector2);

		static Vector2f direction(Vector2f vector1, Vector2f vector2);

		void normalize();
		float getLength();
	};
};