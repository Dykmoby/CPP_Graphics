#include "event_handler.h"
#include "main.h"

using namespace sf;

void EventHandler::handleEvents(RenderWindow &window)
{
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            Program::stopCalculateFlag = true;
            window.close();
        }
    }
}
