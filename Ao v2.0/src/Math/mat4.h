#pragma once

#include "vec3.h"
#include "vec4.h"

namespace ao
{
	//not yet finished
	class mat4
	{
	public:
		mat4();
		~mat4();

		mat4 inverse();

		static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
		static mat4 perspective(float fov, float aspect, float near, float far);

		float& operator[](int i);
		friend mat4 operator*(const mat4& a, const mat4& b);
		friend vec3 operator*(const mat4& a, const vec3& b);
		friend vec3 operator/(const mat4& a, const vec3& b);

		static mat4 identity();
		static mat4 translation(float x, float y, float z);
		static mat4 translation(const vec3& amount);
		static mat4 rotation(const vec3& axis, float degrees);
		static mat4 scale(float x, float y, float z);
	public:
		float elements[16];
	};
}