#include "planets.h"
#include "utils.h"
#include "main.h"
#include <omp.h>

Planet* planets;
unsigned int planetCount = 0;

const float G = 6.6743015E-11f;

unsigned int maxInteractionDistanceSqr = pow(200, 2); // distance must be squared


void Planets::init(int planetCount)
{
	if (::planetCount > 0)
	{
		delete[] planets;
	}

	planets = new Planet[planetCount];
	::planetCount = planetCount;

	for (int i = 0; i < planetCount; i++)
	{
		planets[i].pos.x = (float)Utils::getRandomNumber(0, WIDTH - 1);
		planets[i].pos.y = (float)Utils::getRandomNumber(0, HEIGHT - 1);

		planets[i].radius = (float)Utils::getRandomNumber(1, 8);
		planets[i].mass = 1.9 * 1027 * 1000; // Yupiters * 1000
	}
}

void Planets::calculate(float deltaTime)
{
#pragma omp parallel for
	for (int i = 0; i < planetCount; i++)
	{
		for (int k = 0; k < planetCount; k++)
		{
			if (i == k)
			{
				continue;
			}

			Math::Vector2f delta = planets[i].pos - planets[k].pos;

			float distanceSqr = Math::Vector2f::dot(delta, delta);

			// Collision
			if (distanceSqr < (planets[i].radius + planets[k].radius) * (planets[i].radius + planets[k].radius))
			{
				// delete planet
				continue;
			}

			float invDistanceSqr = 1.0f / distanceSqr;
			Math::Vector2f direction = -delta;
			direction.normalize();

			float velocity = (float) (G * planets[k].mass * planets[i].mass * invDistanceSqr);

			velocity *= deltaTime;

			planets[i].vel = planets[i].vel + direction * velocity;
			if (planets[i].vel.x == INFINITY || planets[i].vel.y == INFINITY)
			{
				planets[i].vel.x = FLT_MAX - 1;
				planets[i].vel.y = FLT_MAX - 1;
			}
		}
	}

#pragma omp parallel for
	for (int i = 0; i < planetCount; i++)
	{
		planets[i].pos.x += planets[i].vel.x;
		planets[i].pos.y += planets[i].vel.y;
	}

	if (frameIsReady == false)
	{
		drawFrame();
	}
}

void Planets::drawFrame()
{
	sf::Image image;
	image.create(WIDTH, HEIGHT, sf::Color::Color(255, 255, 255, 0));

	for (unsigned int i = 0; i < planetCount; i++)
	{
		sf::Color color(255, 255, 255);
		if (planets[i].pos.x + planets[i].radius > 0 && planets[i].pos.x + planets[i].radius < WIDTH && planets[i].pos.y + planets[i].radius > 0 && planets[i].pos.y + planets[i].radius < HEIGHT)
		{
			float radiusSqr = planets[i].radius * planets[i].radius;
			for (int y = (int) -planets[i].radius; y <= planets[i].radius; y++) {
				for (int x = (int) -planets[i].radius; x <= planets[i].radius; x++) {
					if (x * x + y * y <= radiusSqr) {
						//image.setPixel((unsigned int)planets[i].pos.x, (unsigned int)planets[i].pos.y, color);
						if (x + planets[i].pos.x > 0 && x + planets[i].pos.x < WIDTH && y + planets[i].pos.y > 0 && y + planets[i].pos.y < HEIGHT)
						{
							image.setPixel(x + planets[i].pos.x, y + planets[i].pos.y, color);
						}
					}
				}
			}
		}
	}

	images.push_back(image);
	frameIsReady = true;
}