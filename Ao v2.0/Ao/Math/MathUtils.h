#pragma once

#include <math.h>
#include <functional>
#include <random>
#include <ctime>
#include "vec2.h"

const float PI = 355.0f / 113.0f;

inline float toRadians(float degrees)
{
	return (float)(degrees * (PI / 180.0f));
}

inline float toDegrees(float radians)
{
	return (float)(radians * (180.0f / PI));
}

namespace ao
{
	class MathUtils
	{
	private:
		MathUtils() {}

		static std::mt19937& getGenerator()
		{
			static std::mt19937 generator(time(NULL));
			return generator;
		}
		
		static bool ccw(const vec2& a, const vec2& b, const vec2& c)
		{
			return (c.y - a.y) * (b.x - a.x) > (b.y - a.y) * (c.x - a.x);
		}
	public:
		static int randomIntInclusive(int min, int max)
		{
			std::mt19937& generator = getGenerator();
			std::uniform_int_distribution<> dist(min, max);
			return dist(generator);
		}

		static int randomInt(int min, int max)
		{
			std::mt19937& generator = getGenerator();
			std::uniform_int_distribution<> dist(min, max - 1);
			return dist(generator);
		}

		static int randomInt(int max)
		{
			std::mt19937& generator = getGenerator();
			std::uniform_int_distribution<> dist(0, max - 1);
			return dist(generator);
		}

		static float randomFloat()
		{
			std::mt19937& generator = getGenerator();
			std::uniform_real_distribution<float> dist(0.0f, 1.0f);
			return dist(generator);
		}

		static float randomFloat(float min, float max)
		{
			std::mt19937& generator = getGenerator();
			std::uniform_real_distribution<float> dist(min, max);
			return dist(generator);
		}

		static bool linesIntersect(const vec2& a0, const vec2& a1, const vec2& b0, const vec2& b1)
		{
			return ccw(a0, b0, b1) != ccw(a1, b0, b1) && ccw(a0, a1, b0) != ccw(a0, a1, b1);
		}

		static bool pointInsideShape(const vec2& point, const vec2* shape, int numVertices)
		{
			bool c = false;
			int j = numVertices - 1;
			for (int i = 0; i < numVertices; i++)
			{
				if (((shape[i].y > point.y) != (shape[j].y > point.y)) &&
					(point.x < (shape[j].x - shape[i].x) * (point.y - shape[i].y) / (shape[j].y - shape[i].y) + shape[i].x))
					c = !c;
				j = i;
			}
			return c;
		}

		//determines whether shape1 is inside of shape2. Order matters.
		static bool shapesIntersect(const vec2* shape1, int numVertices1, const vec2* shape2, int numVertices2)
		{
			for (int i = 0; i < numVertices1; i++)
			{
				if (pointInsideShape(shape1[i], shape2, numVertices2))
					return true;
			}
			return false;
		}

		static bool pointInsideCircle(const vec2& circlePos, float circleRadius, const vec2& point)
		{
			return vec2::distance(circlePos, point) <= circleRadius;
		}
	};
}

const std::function<float(float)> lerpFunc = [](float t)
{
	return t;
};

const std::function<float(float)> cubicFunc = [](float t)
{
	return -2 * t * t * t + 3 * t * t;
};