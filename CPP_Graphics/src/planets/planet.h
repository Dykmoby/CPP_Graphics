#pragma once
#include "../utils.h"

struct Planet {
	//TODO id

	Utils::Vector2f pos;
	Utils::Vector2f vel;
	float mass = 1;
	float radius = 1;
};