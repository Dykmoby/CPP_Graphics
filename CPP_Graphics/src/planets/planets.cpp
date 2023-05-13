#include <omp.h>

#include "planets.h"
#include "Utils/Random.h"
#include "Math/Consts.h"
#include "main.h"
#include "bodies_simulation.h"
#include "Rendering/Renderer.h"

Planet* planets;
unsigned int planetCount = 0;


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
		planets[i].pos.x = (float)Utils::Random::GetRandomNumber(0, WIDTH - 1);
		planets[i].pos.y = (float)Utils::Random::GetRandomNumber(0, HEIGHT - 1);

		planets[i].radius = Utils::Random::GetRandomNumber(1.0f, 4.0f);
		planets[i].mass = Math::PI * planets[i].radius * planets[i].radius;
	}
}

void Planets::calculate(float deltaTime)
{
	BodiesSimulation::standard(planets, planetCount, deltaTime);
}

void Planets::drawFrame()
{
	sf::Image image;
	image.create(WIDTH, HEIGHT, sf::Color::Color(255, 255, 255, 0));

	for (unsigned int i = 0; i < planetCount; i++)
	{
		if (planets[i].destroyed)
		{
			continue;
		}
		sf::Color color(255, 255, 255);
		if (planets[i].pos.x + planets[i].radius > 0 && planets[i].pos.x + planets[i].radius < WIDTH && planets[i].pos.y + planets[i].radius > 0 && planets[i].pos.y + planets[i].radius < HEIGHT)
		{
			float radiusSqr = planets[i].radius * planets[i].radius;
			for (int y = (int) -planets[i].radius; y <= planets[i].radius; y++) {
				for (int x = (int) -planets[i].radius; x <= planets[i].radius; x++) {
					if (x * x + y * y <= radiusSqr) {
						if (x + planets[i].pos.x > 0 && x + planets[i].pos.x < WIDTH && y + planets[i].pos.y > 0 && y + planets[i].pos.y < HEIGHT)
						{
							image.setPixel(x + planets[i].pos.x, y + planets[i].pos.y, color);
						}
					}
				}
			}
		}
	}

	Renderer::SubmitImage(image);
}