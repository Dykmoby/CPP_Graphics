#pragma once

#include <atomic>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Rendering/layer.h"

const int WIDTH = 800;
const int HEIGHT = 600;

const char fontPath[] = "fonts/QuinqueFive.ttf";

inline std::atomic<bool> frameIsReady = false;
//inline sf::Image mainImage;
inline std::vector<Layer*> layers;
inline sf::RenderWindow mainWindow(sf::VideoMode(WIDTH, HEIGHT), "CPP_Graphics");

class Program
{
public:
    static void start();
    static void init();
    static void calculateCycle();

    inline static std::atomic<bool> stopCalculateFlag;
};