#pragma once

#include <iostream>

namespace ao
{
	class vec3
	{
	public:
		vec3();
		vec3(float x);
		vec3(float x, float y, float z);
		~vec3();

		friend vec3 operator+(const vec3& a, const vec3& b);
		friend vec3 operator+(const vec3& a, float b);
		friend vec3 operator-(const vec3& a, const vec3& b);
		friend vec3 operator-(const vec3& a, float b);
		friend vec3 operator*(const vec3& a, float b);
		friend vec3 operator/(const vec3& a, float b);
		friend vec3 operator-(const vec3& a);
		friend std::ostream& operator<<(std::ostream& stream, const vec3& vec);
		void operator+=(const vec3& a);
		void operator+=(float b);
		void operator-=(const vec3& a);
		void operator-=(float b);
		void operator*=(float b);
		void operator/=(float b);
	public:
		float x, y, z;
	};
}