#pragma once

#include <functional>

namespace ao
{
	class vec2
	{
	public:
		vec2();
		vec2(float x);
		vec2(float x, float y);
		~vec2();

		friend vec2 operator+(const vec2& a, const vec2& b);
		friend vec2 operator+(const vec2& a, float b);
		friend vec2 operator-(const vec2& a, const vec2& b);
		friend vec2 operator-(const vec2& a, float b);
		friend vec2 operator*(const vec2& a, float b);
		friend vec2 operator*(float b, const vec2& a);
		friend vec2 operator/(const vec2& a, float b);
		friend vec2 operator-(const vec2& a);
		friend std::ostream& operator<<(std::ostream& stream, const vec2& vec);
		void operator+=(const vec2& a);
		void operator+=(float b);
		void operator-=(const vec2& a);
		void operator-=(float b);
		void operator*=(float b);
		void operator/=(float b);
		static vec2 lerp(const vec2& v0, const vec2& v1, float t);
		static vec2 cubicInterpolate(const vec2& v0, const vec2& v1, float t);
		static vec2 genericInterpolate(const vec2& v0, const vec2& v1, float t, std::function<float(float)> interpFunc);
	public:
		float x, y;
	};
}