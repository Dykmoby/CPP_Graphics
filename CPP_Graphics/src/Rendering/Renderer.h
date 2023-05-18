#pragma once
#include <SFML/Graphics.hpp>
#include <list>

class Renderer {
public:
	static void SubmitImage(const sf::Image& image);
	static void SubmitTexture(const sf::Texture& texture);
	static void SubmitSprite(const sf::Sprite& sprite);
	static void SubmitText(const sf::Text& text);
	static void Render(sf::RenderWindow& window);
private:
	static std::list<sf::Texture*> textures;
};