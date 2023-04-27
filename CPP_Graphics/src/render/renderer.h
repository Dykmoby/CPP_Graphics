#pragma once
#include <SFML/Graphics.hpp>

static class Renderer {
public:
	static void drawImage(sf::RenderWindow &window, sf::Image image);
	static void drawImages(sf::RenderWindow &window, sf::Image* images, int imageCount);

	static void drawSprite(sf::RenderWindow &window, sf::Sprite sprite);
};