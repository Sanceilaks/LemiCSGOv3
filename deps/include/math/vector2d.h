#pragma once


typedef float vec_t;
class Vector2D {
public:
	vec_t x, y;

	Vector2D(void);
	Vector2D(vec_t X, vec_t Y);
	Vector2D(vec_t* clr);

	void init(vec_t ix = 0.0f, vec_t iy = 0.0f);

	bool is_valid() const;
	void invalidate();

	vec_t operator[](int i) const;
	vec_t& operator[](int i);

	auto Base() -> vec_t*;
	vec_t const* base() const;

	void random(vec_t minVal, vec_t maxVal);
	void zero();

	bool operator==(const Vector2D& v) const;
	bool operator!=(const Vector2D& v) const;

	Vector2D& operator+=(const Vector2D& v) {
		x += v.x; y += v.y;
		return *this;
	}

	Vector2D& operator-=(const Vector2D& v) {
		x -= v.x; y -= v.y;
		return *this;
	}

	Vector2D& operator*=(float fl) {
		x *= fl;
		y *= fl;
		return *this;
	}

	Vector2D& operator*=(const Vector2D& v) {
		x *= v.x;
		y *= v.y;
		return *this;
	}

	Vector2D& operator/=(const Vector2D& v) {
		x /= v.x;
		y /= v.y;
		return *this;
	}

	Vector2D& operator+=(float fl) {
		x += fl;
		y += fl;
		return *this;
	}

	Vector2D& operator/=(float fl) {
		x /= fl;
		y /= fl;
		return *this;
	}
	Vector2D& operator-=(float fl) {
		x -= fl;
		y -= fl;
		return *this;
	}

	void	negate();

	vec_t	length() const;

	vec_t length_sqr(void) const {
		return (x * x + y * y);
	}

	bool is_zero(float tolerance = 0.01f) const {
		return (x > -tolerance && x < tolerance&&
			y > -tolerance && y < tolerance);
	}

	vec_t	normalize_in_place();
	Vector2D	normalized() const;
	bool	is_length_greater_than(float val) const;
	bool	is_length_less_than(float val) const;

	bool within_aa_box(Vector2D const& boxmin, Vector2D const& boxmax);

	vec_t	dist_to(const Vector2D& vOther) const;

	// Get the distance from this vector to the other one squared.
	// NJS: note, VC wasn't inlining it correctly in several deeply nested inlines due to being an 'out of line' .  
	// may be able to tidy this up after switching to VC7
	vec_t dist_to_sqr(const Vector2D& vOther) const {
		Vector2D delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;

		return delta.length_sqr();
	}

	void	copy_to_array(float* rgfl) const;

	// Multiply, add, and assign to this (ie: *this = a + b * scalar). This
	// is about 12% faster than the actual vector equation (because it's done per-component
	// rather than per-vector).
	void	mul_add(const Vector2D& a, const Vector2D& b, float scalar);

	vec_t	dot(const Vector2D& vOther) const;

	Vector2D& operator=(const Vector2D& vOther);

	// 2d
	vec_t	length_2d(void) const;
	vec_t	length_2d_sqr(void) const;

	/// get the component of this vector parallel to some other given vector
	Vector2D  project_onto(const Vector2D& onto);

	Vector2D	operator-(void) const;

	Vector2D	operator+(const Vector2D& v) const;
	Vector2D	operator-(const Vector2D& v) const;
	Vector2D	operator*(const Vector2D& v) const;
	Vector2D	operator/(const Vector2D& v) const;
	Vector2D	operator*(float fl) const;
	Vector2D	operator/(float fl) const;

	Vector2D	cross(const Vector2D& vOther) const;

	Vector2D	get_min(const Vector2D& vOther) const;
	Vector2D	get_max(const Vector2D& vOther) const;
};

