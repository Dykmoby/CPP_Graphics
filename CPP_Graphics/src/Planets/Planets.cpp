#include <omp.h>

#include "Planets.h"
#include "Utils/Random.h"
#include "Math/Consts.h"
#include "Planets/BodiesSimulation.h"
#include "Rendering/Renderer.h"

Planet* planets;
unsigned int planetCount = 0;

int Planets::s_imageWidth;
int Planets::s_imageHeight;
ComputationMode Planets::s_computationType = ComputationMode::CPU_PARALLEL;

void Planets::init(unsigned int planetCount, unsigned int imageWidth, unsigned int imageHeight)
{
	if (::planetCount > 0)
	{
		delete[] planets;
	}
	s_imageWidth = imageWidth;
	s_imageHeight = imageHeight;

	planets = new Planet[planetCount];
	::planetCount = planetCount;

	for (unsigned int i = 0; i < planetCount; i++)
	{
		planets[i].pos.x = (float)Utils::Random::GetRandomNumber(0, imageWidth - 1);
		planets[i].pos.y = (float)Utils::Random::GetRandomNumber(0, imageHeight - 1);

		planets[i].radius = Utils::Random::GetRandomNumber(1.0f, 4.0f);
		planets[i].mass = Math::PI * planets[i].radius * planets[i].radius;
	}
}

void Planets::calculate(double deltaTime)
{
	switch (s_computationType)
	{
	case ComputationMode::CPU_BASIC:
		BodiesSimulation::cpu_basic(planets, planetCount, deltaTime);
		break;
	case ComputationMode::CPU_PARALLEL:
		BodiesSimulation::cpu_parallel(planets, planetCount, deltaTime);
		break;
	}
}

void Planets::DrawFrame()
{
	sf::Image image;
	image.create(s_imageWidth, s_imageHeight, sf::Color::Color(255, 255, 255, 0));

	const int numThreads = std::min(4, static_cast<int>(planetCount));
	std::vector<std::thread> threads(numThreads);

	for (int t = 0; t < numThreads; t++) {
		threads[t] = std::thread([&, t]() {
			for (unsigned int i = t; i < planetCount; i += numThreads) {
				if (planets[i].destroyed)
				{
					continue;
				}
				sf::Color color(255, 255, 255);
				if (planets[i].pos.x + planets[i].radius > 0 && planets[i].pos.x + planets[i].radius < s_imageWidth && planets[i].pos.y + planets[i].radius > 0 && planets[i].pos.y + planets[i].radius < s_imageHeight)
				{
					float radiusSqr = planets[i].radius * planets[i].radius;
					for (int y = (int)-planets[i].radius; y <= planets[i].radius; y++) {
						for (int x = (int)-planets[i].radius; x <= planets[i].radius; x++) {
							if (x * x + y * y <= radiusSqr) {
								if (x + planets[i].pos.x > 0 && x + planets[i].pos.x < s_imageWidth && y + planets[i].pos.y > 0 && y + planets[i].pos.y < s_imageHeight)
								{
									image.setPixel(x + planets[i].pos.x, y + planets[i].pos.y, color);
								}
							}
						}
					}
				}
			}
			});
	}

	for (int t = 0; t < numThreads; t++) {
		threads[t].join();
	}

	Renderer::SubmitImage(image);
}