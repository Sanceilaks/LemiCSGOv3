#include "vector3d.h"

#include <limits>
#include <algorithm>
#include <cmath>

Vector::Vector(void)
{
	invalidate();
}

Vector::Vector(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Vector::Vector(float* clr)
{
	x = clr[0];
	y = clr[1];
	z = clr[2];
}

void Vector::init(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

bool Vector::is_valid() const
{
	return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
}

void Vector::invalidate()
{
	x = y = z = std::numeric_limits<float>::infinity();
}

void Vector::zero()
{
	x = y = z = 0.0f;
}

float* Vector::base()
{
	return reinterpret_cast<float*>(this);
}

float const* Vector::base() const
{
	return reinterpret_cast<float const*>(this);
}

void Vector::clamp()
{
	while (this->x < -180.0f)
		this->x += 360.0f;
	while (this->x > 180.0f)
		this->x -= 360.0f;
	if (this->x > 89.0f)
		this->x = 89.0f;
	if (this->x < -89.0f)
		this->x = -89.0f;
	while (this->y < -180.0f)
		this->y += 360.0f;
	while (this->y > 180.0f)
		this->y -= 360.0f;

	this->z = 0.0f;
}

Vector Vector::clamped()
{
	auto vec = *this;
	vec.clamp();
	return vec;
}

void Vector::copy_to_array(float* buf) const
{
	buf[0] = x;
	buf[1] = y;
	buf[2] = z;
}

void Vector::negative()
{
	x = -x;
	y = -y;
	z = -z;
}

float Vector::dot(const Vector& pos) const
{
	return (x * pos.x + y * pos.y + z * pos.z);
}

float Vector::length()
{
	return sqrt(x * x + y * y + z * z);
}

float Vector::distance(const Vector& to)
{
	Vector delta;
	delta = *this - to;
	return delta.length();
}

Vector& Vector::operator=(const Vector& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
}

float Vector::operator[](int index) const
{
	return ((float*)this)[index];
}

float& Vector::operator[](int index)
{
	return ((float*)this)[index];
}

bool Vector::operator==(const Vector& other)
{
	return ((other.x == x) && (other.y == y) && (other.z == z));
}

bool Vector::operator!=(const Vector& other)
{
	return ((other.x != x) && (other.y != y) && (other.z != z));
}


Vector Vector::operator-() const
{
	return Vector(-x, -y, -z);
}

Vector Vector::operator+(const Vector& other) const
{
	return Vector(x + other.x, y + other.y, z + other.z);
}

Vector Vector::operator-(const Vector& other) const
{
	return Vector(x - other.x, y - other.y, z - other.z);
}

Vector Vector::operator*(const Vector& other) const
{
	return Vector(x * other.x, y * other.y, z * other.z);
}

Vector Vector::operator*(float to)
{
	return Vector(x * to, y * to, z * to);
}

Vector Vector::operator/(const Vector& other) const
{
	return Vector(x / other.x, y / other.y, z / other.z);
}

Vector Vector::operator/(float to)
{
	return Vector(x / to, y / to, z / to);
}
