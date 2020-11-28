#pragma once


typedef float vec_t;
// 3D CVector4D
class Vector4D {
public:
	// Members
	vec_t x, y, z, w;

	// Construction/destruction:
	Vector4D(void);
	Vector4D(vec_t X, vec_t Y, vec_t Z, vec_t W);
	Vector4D(vec_t* clr);

	// Initialization
	void init(vec_t ix = 0.0f, vec_t iy = 0.0f, vec_t iz = 0.0f, vec_t iw = 0.0f);

	// Got any nasty NAN's?
	bool is_valid() const;
	void invalidate();

	// array access...
	vec_t operator[](int i) const;
	vec_t& operator[](int i);

	// Base address...
	vec_t* base();
	vec_t const* base() const;

	// Initialization methods
	void random(vec_t minVal, vec_t maxVal);
	void zero(); ///< zero out a vector

	// equality
	bool operator==(const Vector4D& v) const;
	bool operator!=(const Vector4D& v) const;

	// arithmetic operations
	Vector4D& operator+=(const Vector4D& v) {
		x += v.x; y += v.y; z += v.z; w += v.w;
		return *this;
	}

	Vector4D& operator-=(const Vector4D& v) {
		x -= v.x; y -= v.y; z -= v.z; w -= v.w;
		return *this;
	}

	Vector4D& operator*=(float fl) {
		x *= fl;
		y *= fl;
		z *= fl;
		w *= fl;
		return *this;
	}

	Vector4D& operator*=(const Vector4D& v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
		w *= v.w;
		return *this;
	}

	Vector4D& operator/=(const Vector4D& v) {
		x /= v.x;
		y /= v.y;
		z /= v.z;
		w /= v.w;
		return *this;
	}

	// this ought to be an opcode.
	Vector4D& operator+=(float fl) {
		x += fl;
		y += fl;
		z += fl;
		w += fl;
		return *this;
	}

	// this ought to be an opcode.
	Vector4D& operator/=(float fl) {
		x /= fl;
		y /= fl;
		z /= fl;
		w /= fl;
		return *this;
	}
	Vector4D& operator-=(float fl) {
		x -= fl;
		y -= fl;
		z -= fl;
		w -= fl;
		return *this;
	}

	// negate the vector components
	void	negate();

	// Get the vector's magnitude.
	vec_t	length() const;

	// Get the vector's magnitude squared.
	vec_t length_sqr(void) const {
		return (x * x + y * y + z * z);
	}

	// return true if this vector is (0,0,0) within tolerance
	bool is_zero(float tolerance = 0.01f) const {
		return (x > -tolerance && x < tolerance&&
			y > -tolerance && y < tolerance&&
			z > -tolerance && z < tolerance&&
			w > -tolerance && w < tolerance);
	}

	vec_t	normalize_in_place();
	Vector4D	normalized() const;
	bool	is_length_greater_than(float val) const;
	bool	is_length_less_than(float val) const;

	// check if a vector is within the box defined by two other vectors
	bool within_aa_box(Vector4D const& boxmin, Vector4D const& boxmax);

	// Get the distance from this vector to the other one.
	vec_t	dist_to(const Vector4D& vOther) const;

	// Get the distance from this vector to the other one squared.
	// NJS: note, VC wasn't inlining it correctly in several deeply nested inlines due to being an 'out of line' .  
	// may be able to tidy this up after switching to VC7
	vec_t dist_to_sqr(const Vector4D& vOther) const {
		Vector4D delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;
		delta.z = z - vOther.z;
		delta.w = w - vOther.w;

		return delta.length_sqr();
	}

	// Copy
	void	copy_to_array(float* rgfl) const;

	// Multiply, add, and assign to this (ie: *this = a + b * scalar). This
	// is about 12% faster than the actual vector equation (because it's done per-component
	// rather than per-vector).
	void	mul_add(const Vector4D& a, const Vector4D& b, float scalar);

	// Dot product.
	vec_t	get_dot(const Vector4D& vOther) const;

	// assignment
	Vector4D& operator=(const Vector4D& vOther);

	// 2d
	vec_t	length_2d(void) const;
	vec_t	length_2d_sqr(void) const;

	/// get the component of this vector parallel to some other given vector
	Vector4D  project_onto(const Vector4D& onto);

	// copy constructors
	//	CVector4D(const CVector4D &vOther);

	// arithmetic operations
	Vector4D	operator-(void) const;

	Vector4D	operator+(const Vector4D& v) const;
	Vector4D	operator-(const Vector4D& v) const;
	Vector4D	operator*(const Vector4D& v) const;
	Vector4D	operator/(const Vector4D& v) const;
	Vector4D	operator*(float fl) const;
	Vector4D	operator/(float fl) const;

	// Returns a vector with the min or max in X, Y, and Z.
	Vector4D	Min(const Vector4D& vOther) const;
	Vector4D	Max(const Vector4D& vOther) const;
};