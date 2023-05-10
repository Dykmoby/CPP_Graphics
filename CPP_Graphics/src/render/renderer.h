#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

static class Renderer {
public:
	static void drawImage(sf::RenderWindow &window, sf::Image image);
	static void drawImages(sf::RenderWindow &window, std::vector<sf::Image> imagesVector);

	static void drawSprite(sf::RenderWindow &window, sf::Sprite sprite);
};