#include <SFML/Graphics.hpp>
#include <thread>
#include <atomic>

#include "main.h"
#include "event_handler.h"
#include "render/renderer.h"

using namespace sf;

int main()
{
    Program::start();
    return 0;
}

void Program::start()
{
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "CPP_Graphics");
    Image image;
    image.create(WIDTH, HEIGHT, Color::Black);

    int x = 100;
    int y = 100;
    Color color(255, 0, 0);
    image.setPixel(x, y, color);

    while (window.isOpen())
    {
        EventHandler::handleEvents(window);
        Renderer::drawImage(window, image);
    }
}