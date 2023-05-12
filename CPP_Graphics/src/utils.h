#pragma once

#include <chrono>

class Utils
{
public:
	class Timer {
	public:
		Timer(float* deltaTime) {
			this->deltaTime = deltaTime;
			start_time = std::chrono::high_resolution_clock::now();
		}
		~Timer() {
			current_time = std::chrono::high_resolution_clock::now();
			*deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(current_time - start_time).count();
		}
	private:
		float* deltaTime;
		std::chrono::steady_clock::time_point start_time;
		std::chrono::steady_clock::time_point current_time;
	};
	static int getRandomNumber(int from, int to);
	static float getRandomNumber(float from, float to);
};