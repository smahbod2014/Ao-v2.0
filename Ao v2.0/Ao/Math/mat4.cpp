#include "mat4.h"
#include "MathUtils.h"
#include <cstring>
#include <cassert>

namespace ao
{
	mat4::mat4()
	{
		memset(elements, 0, sizeof(elements));
		elements[0] = 1.0f;
		elements[5] = 1.0f;
		elements[10] = 1.0f;
		elements[15] = 1.0f;
	}

	mat4::~mat4()
	{

	}

	float& mat4::operator[](int i)
	{
		return elements[i];
	}

	mat4 operator*(const mat4& a, const mat4& b)
	{
		mat4 mat;
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				float sum = 0.0f;
				for (int e = 0; e < 4; e++)
				{
					sum += a.elements[x + e * 4] * b.elements[e + y * 4];
				}
				mat.elements[x + y * 4] = sum;
			}
		}

		return mat;
	}

	vec3 operator*(const mat4& a, const vec3& b)
	{
		return vec3(
			a.elements[0] * b.x + a.elements[4] * b.y + a.elements[8] * b.z + a.elements[12],
			a.elements[1] * b.x + a.elements[5] * b.y + a.elements[9] * b.z + a.elements[13],
			a.elements[2] * b.x + a.elements[6] * b.y + a.elements[10] * b.z + a.elements[14]
			);
	}

	vec3 operator/(const mat4& a, const vec3& b)
	{
		return vec3(
			a.elements[0] * b.x + a.elements[4] * b.y + a.elements[8] * b.z,
			a.elements[1] * b.x + a.elements[5] * b.y + a.elements[9] * b.z,
			a.elements[2] * b.x + a.elements[6] * b.y + a.elements[10] * b.z
			);
	}

	mat4 mat4::orthographic(float left, float right, float bottom, float top, float near, float far)
	{
		mat4 mat;

		mat.elements[0 + 0 * 4] = 2.0f / (right - left);

		mat.elements[1 + 1 * 4] = 2.0f / (top - bottom);

		mat.elements[2 + 2 * 4] = 2.0f / (near - far);

		mat.elements[0 + 3 * 4] = (left + right) / (left - right);
		mat.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
		mat.elements[2 + 3 * 4] = (far + near) / (near - far);

		return mat;
	}

	mat4 mat4::perspective(float fov, float aspect, float near, float far)
	{
		mat4 mat;

		float q = 1.0f / tan(toRadians(0.5f * fov));
		float a = q / aspect;

		float b = (near + far) / (near - far);
		float c = (2.0f * near * far) / (near - far);

		mat.elements[0 + 0 * 4] = a;
		mat.elements[1 + 1 * 4] = q;
		mat.elements[2 + 2 * 4] = b;
		mat.elements[3 + 2 * 4] = -1.0f;
		mat.elements[2 + 3 * 4] = c;
		mat.elements[15] = 0.0f;

		return mat;
	}

	mat4 mat4::identity()
	{
		return mat4();
	}

	mat4 mat4::translation(float x, float y, float z)
	{
		mat4 mat;
		mat.elements[12] = x;
		mat.elements[13] = y;
		mat.elements[14] = z;
		return mat;
	}

	mat4 mat4::translation(const vec3& amount)
	{
		mat4 mat;
		mat.elements[12] = amount.x;
		mat.elements[13] = amount.y;
		mat.elements[14] = amount.z;
		return mat;
	}

	mat4 mat4::rotation(const vec3& axis, float degrees)
	{
		mat4 mat;

		float r = toRadians(degrees);
		float c = cosf(r);
		float s = sinf(r);
		float omc = 1.0f - c;

		float x = axis.x;
		float y = axis.y;
		float z = axis.z;

		mat.elements[0 + 0 * 4] = x * omc + c;
		mat.elements[1 + 0 * 4] = y * x * omc + z * s;
		mat.elements[2 + 0 * 4] = x * z * omc - y * s;

		mat.elements[0 + 1 * 4] = x * y * omc - z * s;
		mat.elements[1 + 1 * 4] = y * omc + c;
		mat.elements[2 + 1 * 4] = y * z * omc + x * s;

		mat.elements[0 + 2 * 4] = x * z * omc + y * s;
		mat.elements[1 + 2 * 4] = y * z * omc - x * s;
		mat.elements[2 + 2 * 4] = z * omc + c;

		return mat;
	}

	mat4 mat4::scale(float x, float y, float z)
	{
		mat4 mat;
		mat.elements[0] = x;
		mat.elements[5] = y;
		mat.elements[10] = z;
		return mat;
	}

	//could be improved to not create 32 floats...
	mat4 mat4::inverse()
	{
		float inv[16], det;
		int i;

		inv[0] = elements[5] * elements[10] * elements[15] -
			elements[5] * elements[11] * elements[14] -
			elements[9] * elements[6] * elements[15] +
			elements[9] * elements[7] * elements[14] +
			elements[13] * elements[6] * elements[11] -
			elements[13] * elements[7] * elements[10];

		inv[4] = -elements[4] * elements[10] * elements[15] +
			elements[4] * elements[11] * elements[14] +
			elements[8] * elements[6] * elements[15] -
			elements[8] * elements[7] * elements[14] -
			elements[12] * elements[6] * elements[11] +
			elements[12] * elements[7] * elements[10];

		inv[8] = elements[4] * elements[9] * elements[15] -
			elements[4] * elements[11] * elements[13] -
			elements[8] * elements[5] * elements[15] +
			elements[8] * elements[7] * elements[13] +
			elements[12] * elements[5] * elements[11] -
			elements[12] * elements[7] * elements[9];

		inv[12] = -elements[4] * elements[9] * elements[14] +
			elements[4] * elements[10] * elements[13] +
			elements[8] * elements[5] * elements[14] -
			elements[8] * elements[6] * elements[13] -
			elements[12] * elements[5] * elements[10] +
			elements[12] * elements[6] * elements[9];

		inv[1] = -elements[1] * elements[10] * elements[15] +
			elements[1] * elements[11] * elements[14] +
			elements[9] * elements[2] * elements[15] -
			elements[9] * elements[3] * elements[14] -
			elements[13] * elements[2] * elements[11] +
			elements[13] * elements[3] * elements[10];

		inv[5] = elements[0] * elements[10] * elements[15] -
			elements[0] * elements[11] * elements[14] -
			elements[8] * elements[2] * elements[15] +
			elements[8] * elements[3] * elements[14] +
			elements[12] * elements[2] * elements[11] -
			elements[12] * elements[3] * elements[10];

		inv[9] = -elements[0] * elements[9] * elements[15] +
			elements[0] * elements[11] * elements[13] +
			elements[8] * elements[1] * elements[15] -
			elements[8] * elements[3] * elements[13] -
			elements[12] * elements[1] * elements[11] +
			elements[12] * elements[3] * elements[9];

		inv[13] = elements[0] * elements[9] * elements[14] -
			elements[0] * elements[10] * elements[13] -
			elements[8] * elements[1] * elements[14] +
			elements[8] * elements[2] * elements[13] +
			elements[12] * elements[1] * elements[10] -
			elements[12] * elements[2] * elements[9];

		inv[2] = elements[1] * elements[6] * elements[15] -
			elements[1] * elements[7] * elements[14] -
			elements[5] * elements[2] * elements[15] +
			elements[5] * elements[3] * elements[14] +
			elements[13] * elements[2] * elements[7] -
			elements[13] * elements[3] * elements[6];

		inv[6] = -elements[0] * elements[6] * elements[15] +
			elements[0] * elements[7] * elements[14] +
			elements[4] * elements[2] * elements[15] -
			elements[4] * elements[3] * elements[14] -
			elements[12] * elements[2] * elements[7] +
			elements[12] * elements[3] * elements[6];

		inv[10] = elements[0] * elements[5] * elements[15] -
			elements[0] * elements[7] * elements[13] -
			elements[4] * elements[1] * elements[15] +
			elements[4] * elements[3] * elements[13] +
			elements[12] * elements[1] * elements[7] -
			elements[12] * elements[3] * elements[5];

		inv[14] = -elements[0] * elements[5] * elements[14] +
			elements[0] * elements[6] * elements[13] +
			elements[4] * elements[1] * elements[14] -
			elements[4] * elements[2] * elements[13] -
			elements[12] * elements[1] * elements[6] +
			elements[12] * elements[2] * elements[5];

		inv[3] = -elements[1] * elements[6] * elements[11] +
			elements[1] * elements[7] * elements[10] +
			elements[5] * elements[2] * elements[11] -
			elements[5] * elements[3] * elements[10] -
			elements[9] * elements[2] * elements[7] +
			elements[9] * elements[3] * elements[6];

		inv[7] = elements[0] * elements[6] * elements[11] -
			elements[0] * elements[7] * elements[10] -
			elements[4] * elements[2] * elements[11] +
			elements[4] * elements[3] * elements[10] +
			elements[8] * elements[2] * elements[7] -
			elements[8] * elements[3] * elements[6];

		inv[11] = -elements[0] * elements[5] * elements[11] +
			elements[0] * elements[7] * elements[9] +
			elements[4] * elements[1] * elements[11] -
			elements[4] * elements[3] * elements[9] -
			elements[8] * elements[1] * elements[7] +
			elements[8] * elements[3] * elements[5];

		inv[15] = elements[0] * elements[5] * elements[10] -
			elements[0] * elements[6] * elements[9] -
			elements[4] * elements[1] * elements[10] +
			elements[4] * elements[2] * elements[9] +
			elements[8] * elements[1] * elements[6] -
			elements[8] * elements[2] * elements[5];

		det = elements[0] * inv[0] + elements[1] * inv[4] + elements[2] * inv[8] + elements[3] * inv[12];

		assert(det != 0);

		det = 1.0 / det;

		mat4 result;
		for (i = 0; i < 16; i++)
			result[i] = inv[i] * det;

		return result;
	}
}