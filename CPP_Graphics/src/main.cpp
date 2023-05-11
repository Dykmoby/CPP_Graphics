#include <SFML/Graphics.hpp>
#include <thread>
#include <atomic>
#include <vector>
#include <iostream>

#include "main.h"
#include "event_handler.h"
#include "render/renderer.h"

#include "planets/planets.h"

using namespace sf;

Image mainImage;

int main()
{
	Program::start();
	return 0;
}

void Program::start()
{
	mainImage.create(WIDTH, HEIGHT, Color::Color(2, 5, 20));

	stopCalculateFlag = false;

	std::thread calculateThread(calculateCycle);

	while (mainWindow.isOpen())
	{
		EventHandler::handleEvents(mainWindow);

		if (frameIsReady == true)
		{
			images.insert(images.begin(), mainImage);
			Renderer::drawImages(mainWindow, images);

			std::this_thread::sleep_for(std::chrono::milliseconds(16));
			frameIsReady = false;
			images.clear();
		}
	}

	calculateThread.join();
}

void Program::calculateCycle()
{
	Planets::useDeltaTime = true;
	Planets::init(1000);
	while (stopCalculateFlag != true)
	{
		Planets::calculate();
	}
}