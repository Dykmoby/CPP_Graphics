#include <SFML/Graphics.hpp>
#include <thread>
#include <atomic>
#include <vector>
#include <iostream>
#include <future>

#include "Rendering/Renderer.h"
#include "Utils/Timer.h"

#include "Planets/Planets.h"
#include "Window.h"
#include "Utils/Config.h"


class SimulationWindow : public Window
{
public:
	SimulationWindow() : Window("Simulation", 800, 600) {}
	SimulationWindow(const char* title, int width, int height) : Window(title, width, height) {}
protected:
	void Initialize() override
	{
		std::shared_ptr<Utils::Config> cfg = Utils::Config::Load("config.yaml");

		m_window->setFramerateLimit(60);
		ImGui::SFML::Init(*m_window);

		mainImage.create(m_width, m_height, sf::Color::Color(2, 5, 20));

		font.loadFromFile(fontPath);
		simulationFPSText.setFont(font);
		simulationFPSText.setCharacterSize(15);
		simulationFPSText.setFillColor(sf::Color::Green);
		simulationFPSText.setPosition(10, 10);

		displayFPSText.setFont(font);
		displayFPSText.setCharacterSize(15);
		displayFPSText.setFillColor(sf::Color::Green);
		displayFPSText.setPosition(10, 30);

		stopCalculateFlag = false;

		// TODO: job system (AddJob)
		Planets::init(cfg->GetInt("planets_count"), m_width, m_height);
		physicsThread = std::thread(&SimulationWindow::PhysicsLoop, this);
	}

	void Update(sf::Time deltaTime) override
	{
		RenderLoop(deltaTime);
	}

	void RenderLoop(sf::Time deltaTime)
	{
		Renderer::SubmitImage(mainImage);

		simulationFPSText.setString(std::to_string((int)(1.0f / simulationDeltaTime)));
		Renderer::SubmitText(simulationFPSText);

		displayFPSText.setString(std::to_string((int)(1.0f / deltaTime.asSeconds())));
		Renderer::SubmitText(displayFPSText);

		Planets::DrawFrame();

		ImGui::SFML::Update(*m_window, deltaTime);
		ImGui::ShowDemoWindow();

		ImGui::Begin("Hello, world!");
		ImGui::Button("Look at this pretty button");
		ImGui::End();

		Renderer::Render(*m_window);
	}

	void PhysicsLoop()
	{
		double targetTime = 1.0 / 60;
		double sleepDeltaTime = 0.0f;
		while (stopCalculateFlag != true)
		{
			Utils::Timer simulationTimer(&simulationDeltaTime);
			Utils::Timer sleepTimer(&sleepDeltaTime);

			Planets::calculate(simulationDeltaTime);
			sleepTimer.~Timer();

			// regulate the physics loop to run at the desired FPS
			double sleep_time = targetTime - sleepDeltaTime;
			if (sleep_time > 0)
			{
				std::this_thread::sleep_for(std::chrono::duration<double>(sleep_time));
			}
		}
	}

	void ProcessEvent(sf::Event event) override
	{
		ImGui::SFML::ProcessEvent(*m_window, event);
	}

	void OnClose() override
	{
		stopCalculateFlag = true;
		physicsThread.join();

		ImGui::SFML::Shutdown();
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
	std::shared_ptr<Utils::Config> cfg = Utils::Config::Load(Utils::Config::DEFAULT_CONFIG_PATH.c_str());

	SimulationWindow window("Simulation", cfg->GetInt("window_width"), cfg->GetInt("window_height"));
	window.Start();
	return 0;
}

