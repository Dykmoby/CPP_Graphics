#pragma once

#include "../utils.h"

class Planets
{
public:
    inline static bool useDeltaTime = true;
    static void init(int planetCount);
    static void calculate();
    static void drawFrame();
};

struct Planet {
	//TODO id

	Utils::Vector2f pos;
	Utils::Vector2f vel;
	float mass = 1;
	float radius = 1;
};