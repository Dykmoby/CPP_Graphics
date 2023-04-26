#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "CPP_Graphics");

    sf::Image image;
    image.create(800, 600, sf::Color::Black);

    int x = 100;
    int y = 100;
    sf::Color color(255, 0, 0);
    image.setPixel(x, y, color);

    sf::Texture texture;
    sf::Sprite sprite;
    texture.loadFromImage(image);
    sprite.setTexture(texture);

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();

        sf::sleep(sf::seconds(0.5));
    }

    return 0;
}