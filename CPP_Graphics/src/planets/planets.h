#pragma once
#include "Math/Vector2.h"

class Planets
{
public:
    static void init(int planetCount);
    static void calculate(float deltaTime);
    static void drawFrame();
};

struct Planet {
	//TODO: id

	Math::Vector2f pos;
	Math::Vector2f vel;
	float mass = 1;
	float radius = 1;

	bool destroyed = false;
};