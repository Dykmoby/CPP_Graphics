#pragma once

namespace Math
{
	class Vector2f
	{
	public:
		float x, y;
	public:
		Vector2f();
		Vector2f(float x, float y);

		Vector2f(const Vector2f& v);

		Vector2f& operator=(const Vector2f& vector);
		Vector2f operator*(float num) const;
		Vector2f operator+(const Vector2f& vector) const;
		Vector2f operator-(const Vector2f& vector) const;
		Vector2f operator-() const;

		static float dot(const Vector2f& vector1, const Vector2f& vector2);

		static float distance(const Vector2f& vector1, const Vector2f& vector2);
		static float distanceSqr(const Vector2f& vector1, const Vector2f& vector2);

		void normalize();
		float getLength() const;
	};
}