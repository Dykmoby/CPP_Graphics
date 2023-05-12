#include <SFML/Graphics.hpp>
#include <thread>
#include <atomic>
#include <vector>
#include <iostream>

#include "main.h"
#include "event_handler.h"
#include "Rendering/renderer.h"

#include "planets/planets.h"

using namespace sf;

Image mainImage;

auto start_time = std::chrono::high_resolution_clock::now();
auto current_time = std::chrono::high_resolution_clock::now();
float deltaTime = 0.0f;

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

			frameIsReady = false;
			images.clear();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	calculateThread.join();
}

void Program::calculateCycle()
{
	Planets::init(10000);
	while (stopCalculateFlag != true)
	{
		start_time = std::chrono::high_resolution_clock::now();
		Planets::calculate(deltaTime);
		current_time = std::chrono::high_resolution_clock::now();
		deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(current_time - start_time).count();
		std::cout << (1.0 / deltaTime) << " (" <<  deltaTime << ")" << "\n";
	}
}