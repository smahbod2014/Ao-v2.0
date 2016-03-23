#pragma once

namespace ao
{
	class vec4
	{
	public:
		vec4();
		vec4(float x);
		vec4(float x, float y, float z, float w);
		~vec4();

		friend vec4 operator+(const vec4& a, const vec4& b);
		friend vec4 operator+(const vec4& a, float b);
		friend vec4 operator-(const vec4& a, const vec4& b);
		friend vec4 operator-(const vec4& a, float b);
		friend vec4 operator*(const vec4& a, float b);
		friend vec4 operator/(const vec4& a, float b);
		friend vec4 operator-(const vec4& a);
		void operator+=(const vec4& a);
		void operator+=(float b);
		void operator-=(const vec4& a);
		void operator-=(float b);
		void operator*=(float b);
		void operator/=(float b);
	public:
		float x, y, z, w;
	};
}