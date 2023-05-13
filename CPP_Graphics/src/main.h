#pragma once

#include <atomic>
#include <SFML/Graphics.hpp>
#include <vector>

const int WIDTH = 800;
const int HEIGHT = 600;

const char fontPath[] = "fonts/QuinqueFive.ttf";

inline sf::RenderWindow mainWindow(sf::VideoMode(WIDTH, HEIGHT), "CPP_Graphics");

class Program
{
public:
    static void Start();
    static void Init();
    static void RenderLoop();
    static void PhysicsLoop();

    inline static std::atomic<bool> stopCalculateFlag;
};