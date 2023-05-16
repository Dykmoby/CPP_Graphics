#pragma once
#include <random>
#include <chrono>

namespace Utils 
{
	class Random
	{
	public:
		static int GetRandomNumber(int from, int to)
		{
			std::uniform_int_distribution<> dis(from, to);
			std::mt19937 rnd((unsigned int)std::chrono::steady_clock::now().time_since_epoch().count());
			return dis(rnd);
		}

		static float GetRandomNumber(float from, float to)
		{
			std::uniform_real_distribution<> dis(from, to);
			std::mt19937 rnd((unsigned int)std::chrono::steady_clock::now().time_since_epoch().count());
			return (float)dis(rnd);
		}
	};
}