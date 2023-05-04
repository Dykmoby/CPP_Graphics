#include "planets.h"
#include "planet.h"
#include "../utils.h"
#include "../main.h"

Planet* planets;
unsigned int planetCount = 0;

Planet* planet;

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
		planets[i].x = Utils::getRandomNumber(0, WIDTH - 1);
		planets[i].y = Utils::getRandomNumber(0, HEIGHT - 1);
	}
}

void Planets::calculate()
{


	for (int i = 0; i < planetCount; i++)
	{
		sf::Color color(255, 255, 255);
		mainImage.setPixel(planets[i].x, planets[i].y, color);
	}

	frameIsReady = true;
}
