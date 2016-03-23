#pragma once

#include <math.h>
#include <functional>

const float PI = 355.0f / 113.0f;

inline float toRadians(float degrees)
{
	return (float)(degrees * (PI / 180.0f));
}

inline float toDegrees(float radians)
{
	return (float)(radians * (180.0f / PI));
}

const std::function<float(float)> lerpFunc = [](float t)
{
	return t;
};

const std::function<float(float)> cubicFunc = [](float t)
{
	return -2 * t * t * t + 3 * t * t;
};