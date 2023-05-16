#pragma once
#include "Math/Vector2.h"

class Planets
{
public:
    static void init(unsigned int planetCount, unsigned int imageWidth, unsigned int imageHeight);
    static void calculate(double deltaTime);
    static void drawFrame();
private:
	static int s_imageWidth;
	static int s_imageHeight;
};

struct Planet {
	//TODO: id

	Math::Vector2f pos;
	Math::Vector2f vel;
	float mass = 1;
	float radius = 1;

	bool destroyed = false;
};