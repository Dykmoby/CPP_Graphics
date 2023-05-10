#include <thread>
#include <iostream>
#include <string>
#include <intrin.h>
#include <vector>

#include "planets.h"
#include "planet.h"
#include "../utils.h"
#include "../main.h"

Planet* planets;
unsigned int planetCount = 0;

const float G = 6.6743015E-11f;

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
		planets[i].pos.x = (float) Utils::getRandomNumber(0, WIDTH - 1);
		planets[i].pos.y = (float) Utils::getRandomNumber(0, HEIGHT - 1);
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

			float distance = Utils::Vector2f::distance(planets[i].pos, planets[k].pos);

			if (distance >= 100)
			{
				continue;
			}
			else if (distance < planets[i].radius + planets[k].radius)
			{
				// delete planet
				continue;
			}

			Utils::Vector2f direction = Utils::Vector2f::direction(planets[i].pos, planets[k].pos);
			direction.normalize();

			float velocity = (float) (10000000000 * G * planets[k].mass / (distance * distance));

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
		sf::Image image;
		image.create(WIDTH, HEIGHT, sf::Color::Color(255, 255, 255, 0));

		for (unsigned int i = 0; i < planetCount; i++)
		{
			sf::Color color(255, 255, 255);
			if (planets[i].pos.x > 0 && planets[i].pos.x < WIDTH && planets[i].pos.y > 0 && planets[i].pos.y < HEIGHT)
			{
				image.setPixel((unsigned int) planets[i].pos.x, (unsigned int) planets[i].pos.y, color);
			}
		}

		images.push_back(image);
	}

	frameIsReady = true;
}
