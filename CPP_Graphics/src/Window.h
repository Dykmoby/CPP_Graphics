#pragma once
#include "Utils/Timer.h"
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

class Window
{
protected:
	int m_width;
	int m_height;
	const char* m_title;
	sf::RenderWindow* m_window;
	double m_deltaTime = 0.0f;
public:
	Window() : m_width(800), m_height(600), m_title("Default name")
	{
		m_window = new sf::RenderWindow(sf::VideoMode(m_width, m_height), m_title, sf::Style::Close);
	}

	Window(const char* title, int width, int height) : m_width(width), m_height(height), m_title(title)
	{
		m_window = new sf::RenderWindow(sf::VideoMode(m_width, m_height), m_title, sf::Style::Close);
	}

	~Window()
	{
		m_window->close();
		delete m_window;
	}

	void Start()
	{
		Initialize();
		sf::Clock deltaClock;
		while (m_window->isOpen())
		{
			HandleEvents();
			if (m_window->isOpen())
			{
				Update(deltaClock.restart());
			}
		}
	}
protected:
	virtual void Initialize() {}
	virtual void Update(sf::Time deltaTime) {}
	virtual void ProcessEvent(sf::Event event) {}
	virtual void OnClose() {}
private:
	void HandleEvents()
	{
		sf::Event event;
		while (m_window->pollEvent(event))
		{
			ProcessEvent(event);
			if (event.type == sf::Event::Closed)
			{
				OnClose();
				m_window->close();
			}
		}
	}
};