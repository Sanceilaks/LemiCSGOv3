#pragma once



class Vector
{
public:
	float x, y, z;

	Vector(void);
	Vector(float _x, float _y, float _z);
	Vector(float* clr);

	void init(float _x = 0.f, float _y = 0.f, float _z = 0.f);
	
	bool is_valid() const;
	void invalidate();

	void zero();

	float* base();
	float const* base() const;

	void clamp();
	Vector clamped();

	void copy_to_array(float* buf) const;

	void negative();

	float dot(const Vector& pos) const;

	float length();
	float length2d();
	float length_sqr() const
	{
		return (x * x + y * y + z * z);
	}
	
	float distance(const Vector& to);
	
	Vector& operator=(const Vector& other);
	float operator[](int index) const;
	float& operator[](int index);
	bool operator==(const Vector& other);
	bool operator!=(const Vector& other);
	Vector operator-(void) const;
	Vector operator+(const Vector& other) const;
	Vector operator-(const Vector& other) const;
	Vector operator*(const Vector& other) const;
	Vector operator*(float to);
	Vector operator/(const Vector& other) const;
	Vector operator/(float to);
	Vector operator*=(float f)
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}
};