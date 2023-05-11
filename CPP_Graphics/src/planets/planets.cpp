#include <thread>
#include <iostream>
#include <string>
#include <intrin.h>
#include <vector>

#include "planets.h"
#include "../utils.h"
#include "../main.h"

Planet* planets;
unsigned int planetCount = 0;

const float G = 6.6743015E-11f;

unsigned int maxInteractionDistanceSqr = pow(200, 2); // distance must be squared

auto start_time = std::chrono::high_resolution_clock::now();
auto current_time = std::chrono::high_resolution_clock::now();
float deltaTime = 0.0f;

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
	}
}

void Planets::calculate()
{
	if (Planets::useDeltaTime)
	{
		current_time = std::chrono::high_resolution_clock::now();
		deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(current_time - start_time).count();
		std::cout << deltaTime << "\n";
		start_time = current_time;
	}

 	for (unsigned int i = 0; i < planetCount; i++)
	{
		for (unsigned int k = 0; k < planetCount; k++)
		{
			if (i == k)
			{
				continue;
			}

			float distanceSqr = Utils::Vector2f::distanceSqr(planets[i].pos, planets[k].pos);

			if (distanceSqr > maxInteractionDistanceSqr)
			{
				continue;
			}
			else if (distanceSqr < planets[i].radius + planets[k].radius)
			{
				// delete planet
				continue;
			}

			Utils::Vector2f direction = Utils::Vector2f::direction(planets[i].pos, planets[k].pos);
			direction.normalize();

			float velocity = (float) (10000000000 * G * planets[k].mass / distanceSqr);

			if (Planets::useDeltaTime)
			{
				velocity *= deltaTime;
			}

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