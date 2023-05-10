#pragma once

static class Planets
{
public:
    inline static bool useDeltaTime = true;
    static void init(int planetCount);
    static void calculate();
};