#include "renderer.h"
#include "RenderCommands.h"
#include <list>

struct RendererData
{
	std::list<SpriteDrawCommand> spriteCommands;
	std::list<TextDrawCommand> textCommands;
};
RendererData rendererData;

void Renderer::SubmitImage(const sf::Image& image)
{
	sf::Texture* texture = new sf::Texture();
	sf::Sprite sprite;
	texture->loadFromImage(image);
	sprite.setTexture(*texture, true);
	
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
	window.display();
	rendererData.spriteCommands.clear();
	rendererData.textCommands.clear();
}