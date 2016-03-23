#include "vec4.h"

namespace ao
{
	vec4::vec4()
	{
		x = y = z = w = 0.0f;
	}

	vec4::vec4(float x)
	{
		this->x = this->y = this->z = this->w = x;
	}

	vec4::vec4(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	vec4::~vec4()
	{

	}

	vec4 operator+(const vec4& a, const vec4& b)
	{
		return vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
	}

	vec4 operator+(const vec4& a, float b)
	{
		return vec4(a.x + b, a.y + b, a.z + b, a.w + b);
	}

	vec4 operator-(const vec4& a, const vec4& b)
	{
		return vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
	}

	vec4 operator-(const vec4& a, float b)
	{
		return vec4(a.x - b, a.y - b, a.z - b, a.w - b);
	}

	vec4 operator*(const vec4& a, float b)
	{
		return vec4(a.x * b, a.y * b, a.z * b, a.w * b);
	}

	vec4 operator/(const vec4& a, float b)
	{
		return vec4(a.x / b, a.y / b, a.z / b, a.w / b);
	}

	vec4 operator-(const vec4& a)
	{
		return vec4(-a.x, -a.y, -a.z, -a.w);
	}

	void vec4::operator+=(const vec4& a)
	{
		x += a.x;
		y += a.y;
		z += a.z;
		w += a.w;
	}

	void vec4::operator+=(float b)
	{
		x += b;
		y += b;
		z += b;
		w += b;
	}

	void vec4::operator-=(const vec4& a)
	{
		x -= a.x;
		y -= a.y;
		z -= a.z;
		w -= a.w;
	}

	void vec4::operator-=(float b)
	{
		x -= b;
		y -= b;
		z -= b;
		w -= b;
	}

	void vec4::operator*=(float b)
	{
		x *= b;
		y *= b;
		z *= b;
		w *= b;
	}

	void vec4::operator/=(float b)
	{
		x /= b;
		y /= b;
		z /= b;
		w /= b;
	}
}