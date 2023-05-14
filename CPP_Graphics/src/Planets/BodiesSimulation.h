#pragma once
#include "Planets.h"

class BodiesSimulation
{
public:
	static void standard(Planet *planets, unsigned int planetCount, double deltaTime);
};