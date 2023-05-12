#pragma once
#include "planets.h"

const float G = 6.6743015E-11f;

class BodiesSimulation
{
public:
	static void standard(Planet *planets, unsigned int planetCount, float deltaTime);
};