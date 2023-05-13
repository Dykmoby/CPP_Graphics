#include <SFML/Graphics.hpp>
#include <thread>
#include <atomic>
#include <vector>
#include <iostream>

#include "main.h"
#include "event_handler.h"
#include "Rendering/renderer.h"
#include "Utils/Timer.h"

#include "planets/planets.h"

using namespace sf;

Image mainImage;
Font font;
Text simulationFPSText;
Text displayFPSText;

float simulationDeltaTime = 0.0f;

float displayDeltaTime = 0.0f;

std::thread physicsThread;

int main()
{
	Program::Start();
	return 0;
}

void Program::Start()
{
	Init();

	physicsThread = std::thread(PhysicsLoop);

	RenderLoop();
	

	physicsThread.join();
}

void Program::Init()
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

void Program::RenderLoop()
{
	auto lastDisplayTime = std::chrono::high_resolution_clock::now();
	float targetTime = 1 / 60.0;
	while (mainWindow.isOpen())
	{
		EventHandler::handleEvents(mainWindow);
		std::cout << "Unlock render" << std::endl;

		Renderer::SubmitImage(mainImage);

		simulationFPSText.setString(std::to_string((int)(1.0f / simulationDeltaTime)));
		Renderer::SubmitText(simulationFPSText);

		auto currentTime = std::chrono::high_resolution_clock::now();
		displayDeltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - lastDisplayTime).count();
		displayFPSText.setString(std::to_string((int)(1.0f / displayDeltaTime)));
		Renderer::SubmitText(displayFPSText);
		std::cout << "Display FPS: " << 1.0f / displayDeltaTime << std::endl;

		Planets::drawFrame();

		Renderer::Render(mainWindow);
		lastDisplayTime = std::chrono::high_resolution_clock::now();

		// Fix execution speed
		float timeToTarget = targetTime - displayDeltaTime;
		if (timeToTarget > 0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds((int)(timeToTarget * 1000)));
		}
	}
}

void Program::PhysicsLoop()
{
	Planets::init(100);
	float targetTime = 1 / 60.0;

	float waitDeltaTime = 0.0f;
	while (stopCalculateFlag != true)
	{
		Utils::Timer simulationTimer(&simulationDeltaTime);
		{
			Utils::Timer simulationTimer(&simulationDeltaTime);
			Planets::calculate(simulationDeltaTime);
		}
		// Fix execution speed
		float timeToTarget = targetTime - simulationDeltaTime;
		while (timeToTarget > 0)
		{
			Utils::Timer simulationTimer(&waitDeltaTime);
			timeToTarget -= waitDeltaTime;
		}
	}
}