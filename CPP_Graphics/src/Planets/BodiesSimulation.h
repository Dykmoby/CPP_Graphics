#pragma once
#include "planets.h"

class BodiesSimulation
{
public:
	static void standard(Planet *planets, unsigned int planetCount, double deltaTime);
};