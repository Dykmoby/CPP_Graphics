#include <random>

#include "utils.h"

std::random_device rd;
std::mt19937 gen(rd());

int Utils::getRandomNumber(int from, int to)
{
	std::uniform_int_distribution<> dis(from, to);
	return dis(gen);
}
