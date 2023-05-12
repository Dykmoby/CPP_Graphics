#include <vector>

#include "renderer.h"
#include "layer.h"

using namespace sf;

void Renderer::drawImage(RenderWindow &window, Image image)
{
	Texture texture;
	Sprite sprite;
	texture.loadFromImage(image);
	sprite.setTexture(texture);

	drawSprite(window, sprite);
}

void Renderer::drawTexture(RenderWindow& window, Texture texture)
{
	Sprite sprite;
	sprite.setTexture(texture);

	drawSprite(window, sprite);
}

void Renderer::drawSprite(RenderWindow& window, Sprite sprite)
{
	window.draw(sprite);
}

void Renderer::drawText(RenderWindow& window, Text text)
{
	window.draw(text);
}

void Renderer::displayLayers(RenderWindow& window, std::vector<Layer*> layerVector)
{
	window.clear();
	for (Layer* layer : layerVector)
	{
		switch (layer->getType()) {
		case LayerType::IMAGE: {
			LayerImage* layerImage = dynamic_cast<LayerImage*>(layer);
			drawImage(window, layerImage->image);
			break;
		}
		case LayerType::TEXTURE: {
			LayerTexture* layerTexture = dynamic_cast<LayerTexture*>(layer);
			drawTexture(window, layerTexture->texture);
			break;
		}
		case LayerType::SPRITE: {
			LayerSprite* layerSprite = dynamic_cast<LayerSprite*>(layer);
			drawSprite(window, layerSprite->sprite);
			break;
		}
		case LayerType::TEXT: {
			LayerText* layerText = dynamic_cast<LayerText*>(layer);
			drawText(window, layerText->text);
			break;
		}
		}
	}
	window.display();
}