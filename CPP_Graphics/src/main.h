#pragma once

#include <atomic>
#include <SFML/Graphics.hpp>

const int WIDTH = 800;
const int HEIGHT = 600;

inline std::atomic<bool> frameIsReady = false;
inline sf::Image mainImage;
inline sf::RenderWindow mainWindow(sf::VideoMode(WIDTH, HEIGHT), "CPP_Graphics");

static class Program
{
public:
    static void start();
    static void calculateCycle();

    inline static std::atomic<bool> stopCalculateFlag;
};