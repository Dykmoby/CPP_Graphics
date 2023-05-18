#include <SFML/Graphics.hpp>
#include <thread>
#include <atomic>
#include <vector>
#include <iostream>
#include <future>

#include "Rendering/renderer.h"
#include "Utils/Timer.h"

#include "planets/planets.h"
#include "Window.h"



class SimulationWindow : public Window
{
public:
	SimulationWindow() : Window("Simulation", 800, 600) {}
protected:
	void Initialize() override
	{
		m_window->setFramerateLimit(144);

		mainImage.create(m_width, m_height, sf::Color::Color(2, 5, 20));

		font.loadFromFile(fontPath);
		simulationFPSText.setFont(font);
		simulationFPSText.setCharacterSize(64);
		simulationFPSText.setColor(sf::Color::Green);
		simulationFPSText.setPosition(10, 10);

		displayFPSText.setFont(font);
		displayFPSText.setCharacterSize(64);
		displayFPSText.setColor(sf::Color::Green);
		displayFPSText.setPosition(10, 90);

		stopCalculateFlag = false;

		// TODO: job system (AddJob)
		Planets::init(10000, m_width, m_height);
		physicsThread = std::thread(&SimulationWindow::PhysicsLoop, this);
	}

	void Update(float deltaTime) override
	{
		RenderLoop(deltaTime);
	}

	void RenderLoop(float deltaTime)
	{
		Renderer::SubmitImage(mainImage);

		simulationFPSText.setString(std::to_string((int)(1.0f / simulationDeltaTime)));
		Renderer::SubmitText(simulationFPSText);

		displayFPSText.setString(std::to_string((int)(1.0f / deltaTime)));
		Renderer::SubmitText(displayFPSText);

		Planets::drawFrame();
		Renderer::Render(*m_window);
	}

	void PhysicsLoop()
	{
		double targetTime = 1000.0 / 1000;
		double sleepDeltaTime = 0.0f;
		while (stopCalculateFlag != true)
		{
			Utils::Timer simulationTimer(&simulationDeltaTime);
			Planets::calculate(simulationDeltaTime);
			std::cout << "Simulation time: " << simulationDeltaTime << std::endl;

			// regulate the physics loop to run at the desired FPS
			double sleep_time = targetTime - simulationDeltaTime;
			if (sleep_time > 0)
			{
				std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(sleep_time));
			}
		}
	}

	void OnClose() override
	{
		physicsThread.join();
	}

	void OnEvent(sf::Event event) override
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Num1)
			{
				Planets::SetComputationMode(CPU_BASIC);
			}
			else if (event.key.code == sf::Keyboard::Num2)
			{
				Planets::SetComputationMode(CPU_PARALLEL);
			}
			else if (event.key.code == sf::Keyboard::Num3)
			{
				Planets::SetComputationMode(GPU_PARALLEL);
			}
		}
	}

private:
	const char* fontPath = "fonts/QuinqueFive.ttf";
	inline static std::atomic<bool> stopCalculateFlag;
	sf::Image mainImage;
	sf::Font font;
	sf::Text simulationFPSText;
	sf::Text displayFPSText;

	double simulationDeltaTime = 0.0f;

	std::thread physicsThread;
};

int main()
{
	SimulationWindow window;
	window.Start();
	return 0;
}

