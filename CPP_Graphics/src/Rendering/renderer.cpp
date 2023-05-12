#include <vector>

#include "renderer.h"

using namespace sf;

void Renderer::drawImage(RenderWindow &window, Image image)
{
    Texture texture;
    Sprite sprite;
    texture.loadFromImage(image);
    sprite.setTexture(texture);

    drawSprite(window, sprite);
}

void Renderer::drawImages(RenderWindow& window, std::vector<Image> imagesVector)
{
    window.clear();
    for (Image image : imagesVector)
    {
        Texture texture;
        Sprite sprite;
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        window.draw(sprite);
    }
    window.display();
}

void Renderer::drawSprite(RenderWindow& window, Sprite sprite)
{
    window.clear();
    window.draw(sprite);
    window.display();
}