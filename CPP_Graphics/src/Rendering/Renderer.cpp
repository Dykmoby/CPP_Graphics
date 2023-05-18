#include "Renderer.h"
#include "RenderCommands.h"
#include <list>
#include "imgui.h"
#include "imgui-SFML.h"

struct RendererData
{
	std::list<SpriteDrawCommand> spriteCommands;
	std::list<TextDrawCommand> textCommands;
};
RendererData rendererData;

std::list<sf::Texture*> Renderer::textures;

void Renderer::SubmitImage(const sf::Image& image)
{
	sf::Texture* texture = new sf::Texture();
	sf::Sprite sprite;
	texture->loadFromImage(image);
	sprite.setTexture(*texture, true);

	textures.push_back(texture);
	SubmitSprite(sprite);
}

void Renderer::SubmitTexture(const sf::Texture& texture)
{
	sf::Sprite sprite;
	sprite.setTexture(texture);

	SubmitSprite(sprite);
}

void Renderer::SubmitSprite(const sf::Sprite& sprite)
{
	rendererData.spriteCommands.push_back(SpriteDrawCommand(sprite));
}

void Renderer::SubmitText(const sf::Text& text)
{
	rendererData.textCommands.push_back(TextDrawCommand(text));
}

void Renderer::Render(sf::RenderWindow& window)
{
	window.clear();
	for (SpriteDrawCommand command : rendererData.spriteCommands)
	{
		window.draw(command.sprite);
	}

	for (TextDrawCommand command : rendererData.textCommands)
	{
		window.draw(command.text);
	}

	ImGui::SFML::Render(window);

	window.display();

	rendererData.spriteCommands.clear();
	rendererData.textCommands.clear();
	for (sf::Texture* texture : textures)
	{
		delete texture;
	}
	textures.clear();
}