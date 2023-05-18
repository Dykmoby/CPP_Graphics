#pragma once
#include "planets.h"

class BodiesSimulation
{
public:
	static void cpu_basic(Planet* planets, unsigned int planetCount, double deltaTime);
	static void cpu_parallel(Planet* planets, unsigned int planetCount, double deltaTime);
};