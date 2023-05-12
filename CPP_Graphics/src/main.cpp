#include <SFML/Graphics.hpp>
#include <thread>
#include <atomic>
#include <vector>
#include <iostream>

#include "main.h"
#include "event_handler.h"
#include "Rendering/renderer.h"
#include "Rendering/layer.h"
#include "utils.h"

#include "planets/planets.h"

using namespace sf;

Image mainImage;
Font font;
Text simulationFPSText;
Text displayFPSText;

float simulationDeltaTime = 0.0f;

auto lastDisplayTime = std::chrono::high_resolution_clock::now();
float displayDeltaTime = 0.0f;

int main()
{
	Program::start();
	return 0;
}

void Program::start()
{
	init();

	std::thread calculateThread(calculateCycle);

	while (mainWindow.isOpen())
	{
		EventHandler::handleEvents(mainWindow);

		if (frameIsReady == true)
		{
			layers.insert(layers.begin(), new LayerImage(mainImage));

			simulationFPSText.setString(std::to_string((int) (1.0f / simulationDeltaTime)));
			layers.push_back(new LayerText(simulationFPSText));

			auto currentTime = std::chrono::high_resolution_clock::now();
			displayDeltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - lastDisplayTime).count();
			displayFPSText.setString(std::to_string((int)(1.0f / displayDeltaTime)));
			layers.push_back(new LayerText(displayFPSText));

			Renderer::displayLayers(mainWindow, layers);
			lastDisplayTime = std::chrono::high_resolution_clock::now();

			for (Layer* layer : layers)
			{
				layer->~Layer();
			}

			frameIsReady = false;
			layers.clear();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	calculateThread.join();
}

void Program::init()
{
	mainImage.create(WIDTH, HEIGHT, Color::Color(2, 5, 20));

	font.loadFromFile(fontPath);
	simulationFPSText.setFont(font);
	simulationFPSText.setCharacterSize(15);
	simulationFPSText.setColor(sf::Color::Green);
	simulationFPSText.setPosition(10, 10);

	displayFPSText.setFont(font);
	displayFPSText.setCharacterSize(15);
	displayFPSText.setColor(sf::Color::Green);
	displayFPSText.setPosition(10, 30);

	stopCalculateFlag = false;
}

void Program::calculateCycle()
{
	Planets::init(1000);
	while (stopCalculateFlag != true)
	{
		Utils::Timer simulationTimer(&simulationDeltaTime);
		Planets::calculate(simulationDeltaTime);
	}
}