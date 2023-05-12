#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "layer.h"

class Renderer {
public:
	static void drawImage(sf::RenderWindow &window, sf::Image image);
	static void drawTexture(sf::RenderWindow &window, sf::Texture texture);
	static void drawSprite(sf::RenderWindow& window, sf::Sprite sprite);
	static void drawText(sf::RenderWindow& window, sf::Text text);
	static void displayLayers(sf::RenderWindow& window, std::vector<Layer*> layerVector);
};