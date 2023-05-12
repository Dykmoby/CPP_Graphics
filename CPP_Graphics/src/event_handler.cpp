#include "event_handler.h"
#include "main.h"

void EventHandler::handleEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            Program::stopCalculateFlag = true;
            window.close();
        }
    }
}
