#include "BodiesSimulation.h"
#include "Math/Consts.h"
#include <cmath>

void BodiesSimulation::standard(Planet *planets, unsigned int planetCount, double deltaTime)
{
#pragma omp parallel for
	for (unsigned int i = 0; i < planetCount; i++)
	{
		if (planets[i].destroyed)
		{
			continue;
		}
		for (unsigned int k = 0; k < planetCount; k++)
		{
			if (i == k || planets[k].destroyed)
			{
				continue;
			}

			Math::Vector2f delta = planets[i].pos - planets[k].pos;

			float distanceSqr = Math::Vector2f::dot(delta, delta);

			// Collision
			if (distanceSqr < (planets[i].radius + planets[k].radius) * (planets[i].radius + planets[k].radius))
			{
				if (planets[i].mass > planets[k].mass)
				{
					planets[i].mass += planets[k].mass;
					planets[i].vel = planets[i].vel + planets[k].vel * planets[k].mass / planets[i].mass;
					planets[k].destroyed = true;
					continue;
				}
				else
				{
					planets[k].mass += planets[i].mass;
					planets[k].vel = planets[k].vel + planets[i].vel * planets[i].mass / planets[k].mass;
					planets[i].destroyed = true;
					break;
				}
			}

			float invDistanceSqr = 1.0f / distanceSqr;
			Math::Vector2f direction = delta;
			direction.normalize();

			float velocity = (float)(100000000000 * Math::G * planets[k].mass * invDistanceSqr);
			velocity *= (float) (deltaTime * deltaTime);

			planets[i].vel = planets[i].vel + direction * velocity;

			if (planets[i].vel.x == INFINITY || planets[i].vel.y == INFINITY)
			{
				planets[i].vel.x = FLT_MAX - 1;
				planets[i].vel.y = FLT_MAX - 1;
			}
		}
	}

#pragma omp parallel for
	for (unsigned int i = 0; i < planetCount; i++)
	{
		planets[i].pos.x += planets[i].vel.x;
		planets[i].pos.y += planets[i].vel.y;
	}
}