#include <random>
#include <chrono>

#include "utils.h"

int Utils::getRandomNumber(int from, int to)
{
	std::uniform_int_distribution<> dis(from, to);
	std::mt19937 rnd((unsigned int) std::chrono::steady_clock::now().time_since_epoch().count());
	return dis(rnd);
}

float Utils::getRandomNumber(float from, float to)
{
	std::uniform_real_distribution<> dis(from, to);
	std::mt19937 rnd((unsigned int)std::chrono::steady_clock::now().time_since_epoch().count());
	return dis(rnd);
}

