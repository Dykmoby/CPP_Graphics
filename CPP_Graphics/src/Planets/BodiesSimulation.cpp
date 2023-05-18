#include "BodiesSimulation.h"
#include "Math/Consts.h"
#include <cmath>
#include <vector>
#include <thread>

void BodiesSimulation::cpu_basic(Planet* planets, unsigned int planetCount, double deltaTime)
{
	for (int i = 0; i < planetCount; i++)
	{
		if (planets[i].destroyed)
		{
			continue;
		}
		for (int k = 0; k < planetCount; k++)
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

			float velocity = (float)(100000 * Math::G * planets[k].mass * invDistanceSqr);
			velocity *= deltaTime * deltaTime;

			planets[i].vel = planets[i].vel + direction * velocity;

			if (planets[i].vel.x == INFINITY || planets[i].vel.y == INFINITY)
			{
				planets[i].vel.x = FLT_MAX - 1;
				planets[i].vel.y = FLT_MAX - 1;
			}
		}
	}

	for (unsigned int i = 0; i < planetCount; i++)
	{
		planets[i].pos.x += planets[i].vel.x;
		planets[i].pos.y += planets[i].vel.y;
	}
}

void cpu_thread(Planet* planets, unsigned int planetCount, double deltaTime, int start, int threadCount)
{
	for (int i = start; i < planetCount; i+=threadCount)
	{
		if (planets[i].destroyed)
		{
			continue;
		}
		for (int k = 0; k < planetCount; k++)
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

			float velocity = (float)(100000 * Math::G * planets[k].mass * invDistanceSqr);
			velocity *= deltaTime * deltaTime;

			planets[i].vel = planets[i].vel + direction * velocity;

			if (planets[i].vel.x == INFINITY || planets[i].vel.y == INFINITY)
			{
				planets[i].vel.x = FLT_MAX - 1;
				planets[i].vel.y = FLT_MAX - 1;
			}
		}
	}
}

void BodiesSimulation::cpu_parallel(Planet *planets, unsigned int planetCount, double deltaTime)
{
	const int numThreads = std::min(8, static_cast<int>(planetCount));
	std::vector<std::thread> threads(numThreads);

	for (int t = 0; t < numThreads; t++) {
		threads[t] = std::thread([&, t]() {
			cpu_thread(planets, planetCount, deltaTime, t, numThreads);
			});
	}
	
	for (int t = 0; t < numThreads; t++) {
		threads[t].join();
	}
#pragma omp parallel for
	for (unsigned int i = 0; i < planetCount; i++)
	{
		planets[i].pos.x += planets[i].vel.x;
		planets[i].pos.y += planets[i].vel.y;
	}
}