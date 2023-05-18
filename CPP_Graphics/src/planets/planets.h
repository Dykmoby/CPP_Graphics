#pragma once
#include "Math/Vector2.h"

enum ComputationMode
{
	CPU_BASIC,
	CPU_PARALLEL,
	GPU_PARALLEL
};

class Planets
{
public:
    static void init(int planetCount, int imageWidth, int imageHeight);
    static void calculate(double deltaTime);
    static void drawFrame();
	static void SetComputationMode(ComputationMode mode) { s_computationType = mode; }
private:
	static int s_imageWidth;
	static int s_imageHeight;
	static ComputationMode s_computationType;
};

struct Planet {
	//TODO: id

	Math::Vector2f pos;
	Math::Vector2f vel;
	float mass = 1;
	float radius = 1;

	bool destroyed = false;
};