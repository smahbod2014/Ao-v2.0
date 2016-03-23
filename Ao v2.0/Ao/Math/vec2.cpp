#include "vec2.h"
#include "MathUtils.h"

namespace ao
{
	vec2::vec2()
	{
		x = y = 0.0f;
	}

	vec2::vec2(float x)
	{
		this->x = this->y = x;
	}

	vec2::vec2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	vec2::~vec2()
	{

	}

	vec2 operator+(const vec2& a, const vec2& b)
	{
		return vec2(a.x + b.x, a.y + b.y);
	}

	vec2 operator+(const vec2& a, float b)
	{
		return vec2(a.x + b, a.y + b);
	}

	vec2 operator-(const vec2& a, const vec2& b)
	{
		return vec2(a.x - b.x, a.y - b.y);
	}

	vec2 operator-(const vec2& a, float b)
	{
		return vec2(a.x - b, a.y - b);
	}

	vec2 operator*(const vec2& a, float b)
	{
		return vec2(a.x * b, a.y * b);
	}

	vec2 operator*(float b, const vec2& a)
	{
		return vec2(a.x * b, a.y * b);
	}

	vec2 operator/(const vec2& a, float b)
	{
		return vec2(a.x / b, a.y / b);
	}

	vec2 operator-(const vec2& a)
	{
		return vec2(-a.x, -a.y);
	}

	std::ostream& operator<<(std::ostream& stream, const vec2& vec)
	{
		//stream << "(" << vec.x << ", " << vec.y << ")";
		return stream;
	}

	void vec2::operator+=(const vec2& a)
	{
		x += a.x;
		y += a.y;
	}

	void vec2::operator+=(float b)
	{
		x += b;
		y += b;
	}

	void vec2::operator-=(const vec2& a)
	{
		x -= a.x;
		y -= a.y;
	}

	void vec2::operator-=(float b)
	{
		x -= b;
		y -= b;
	}

	void vec2::operator*=(float b)
	{
		x *= b;
		y *= b;
	}

	void vec2::operator/=(float b)
	{
		x /= b;
		y /= b;
	}

	vec2 vec2::lerp(const vec2& v0, const vec2& v1, float t)
	{
		return (1 - t) * v0 + t * v1;
	}

	vec2 vec2::cubicInterpolate(const vec2& v0, const vec2& v1, float t)
	{
		return cubicFunc(1 - t) * v0 + cubicFunc(t) * v1;
	}

	vec2 vec2::genericInterpolate(const vec2& v0, const vec2& v1, float t, std::function<float(float)> interpFunc)
	{
		return interpFunc(1 - t) * v0 + interpFunc(t) * v1;
	}
}