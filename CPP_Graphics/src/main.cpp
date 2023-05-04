#include <SFML/Graphics.hpp>
#include <thread>
#include <atomic>

#include "main.h"
#include "event_handler.h"
#include "render/renderer.h"

#include "planets/planets.h"

using namespace sf;

int main()
{
    Program::start();
    return 0;
}

void Program::start()
{
    mainImage.create(WIDTH, HEIGHT, Color::Black);

    stopCalculateFlag = false;

    std::thread calculateThread(calculateCycle);

    while (mainWindow.isOpen())
    {
        EventHandler::handleEvents(mainWindow);

        if (frameIsReady == true)
        {
            Renderer::drawImage(mainWindow, mainImage);
            frameIsReady = false;
        }
    }

    calculateThread.join();
}

void Program::calculateCycle()
{
    Planets::init(500);

    while (stopCalculateFlag != true)
    {
        Planets::calculate();
    }
}