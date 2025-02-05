#include "vector4d.h"

#include <cmath>
#include <limits>

void VectorCopy(const Vector4D& src, Vector4D& dst) {
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
	dst.w = src.w;
}
void VectorLerp(const Vector4D& src1, const Vector4D& src2, vec_t t, Vector4D& dest) {
	dest.x = src1.x + (src2.x - src1.x) * t;
	dest.y = src1.y + (src2.y - src1.y) * t;
	dest.z = src1.z + (src2.z - src1.z) * t;
	dest.w = src1.w + (src2.w - src1.w) * t;
}
float VectorLength(const Vector4D& v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

vec_t NormalizeVector(Vector4D& v) {
	vec_t l = v.length();
	if (l != 0.0f) {
		v /= l;
	}
	else {
		v.x = v.y = v.z = v.w = 0.0f;
	}
	return l;
}

Vector4D::Vector4D(void) {
	invalidate();
}
Vector4D::Vector4D(vec_t X, vec_t Y, vec_t Z, vec_t W) {
	x = X;
	y = Y;
	z = Z;
	w = W;
}
Vector4D::Vector4D(vec_t* clr) {
	x = clr[0];
	y = clr[1];
	z = clr[2];
	w = clr[3];
}

//-----------------------------------------------------------------------------
// initialization
//-----------------------------------------------------------------------------

void Vector4D::init(vec_t ix, vec_t iy, vec_t iz, vec_t iw) {
	x = ix; y = iy; z = iz; w = iw;
}

void Vector4D::random(vec_t minVal, vec_t maxVal) {
	x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	z = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	w = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
}

// This should really be a single opcode on the PowerPC (move r0 onto the vec reg)
void Vector4D::zero() {
	x = y = z = w = 0.0f;
}

//-----------------------------------------------------------------------------
// assignment
//-----------------------------------------------------------------------------

Vector4D& Vector4D::operator=(const Vector4D& vOther) {
	x = vOther.x; y = vOther.y; z = vOther.z; w = vOther.w;
	return *this;
}


//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------
vec_t& Vector4D::operator[](int i) {
	return ((vec_t*)this)[i];
}

vec_t Vector4D::operator[](int i) const {
	return ((vec_t*)this)[i];
}


//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------
vec_t* Vector4D::base() {
	return (vec_t*)this;
}

vec_t const* Vector4D::base() const {
	return (vec_t const*)this;
}

//-----------------------------------------------------------------------------
// IsValid?
//-----------------------------------------------------------------------------

bool Vector4D::is_valid() const {
	return !isinf(x) && !isinf(y) && !isinf(z) && !isinf(w);
}

//-----------------------------------------------------------------------------
// Invalidate
//-----------------------------------------------------------------------------

void Vector4D::invalidate() {
	//#ifdef _DEBUG
	//#ifdef VECTOR_PARANOIA
	x = y = z = w = std::numeric_limits<float>::infinity();
	//#endif
	//#endif
}

//-----------------------------------------------------------------------------
// comparison
//-----------------------------------------------------------------------------

bool Vector4D::operator==(const Vector4D& src) const {
	return (src.x == x) && (src.y == y) && (src.z == z) && (src.w == w);
}

bool Vector4D::operator!=(const Vector4D& src) const {
	return (src.x != x) || (src.y != y) || (src.z != z) || (src.w != w);
}


//-----------------------------------------------------------------------------
// Copy
//-----------------------------------------------------------------------------
void	Vector4D::copy_to_array(float* rgfl) const {
	rgfl[0] = x, rgfl[1] = y, rgfl[2] = z; rgfl[3] = w;
}

//-----------------------------------------------------------------------------
// standard math operations
//-----------------------------------------------------------------------------
// #pragma message("TODO: these should be SSE")

void Vector4D::negate() {
	x = -x; y = -y; z = -z; w = -w;
}

// get the component of this vector parallel to some other given vector
Vector4D Vector4D::project_onto(const Vector4D& onto) {
	return onto * (this->get_dot(onto) / (onto.length_sqr()));
}

// FIXME: Remove
// For backwards compatability
void	Vector4D::mul_add(const Vector4D& a, const Vector4D& b, float scalar) {
	x = a.x + b.x * scalar;
	y = a.y + b.y * scalar;
	z = a.z + b.z * scalar;
	w = a.w + b.w * scalar;
}

Vector4D VectorLerp(const Vector4D& src1, const Vector4D& src2, vec_t t) {
	Vector4D result;
	VectorLerp(src1, src2, t, result);
	return result;
}

vec_t Vector4D::get_dot(const Vector4D& b) const {
	return (x * b.x + y * b.y + z * b.z + w * b.w);
}
void VectorClear(Vector4D& a) {
	a.x = a.y = a.z = a.w = 0.0f;
}

vec_t Vector4D::length(void) const {
	return sqrt(x * x + y * y + z * z + w * w);
}

// check a point against a box
bool Vector4D::within_aa_box(Vector4D const& boxmin, Vector4D const& boxmax) {
	return (
		(x >= boxmin.x) && (x <= boxmax.x) &&
		(y >= boxmin.y) && (y <= boxmax.y) &&
		(z >= boxmin.z) && (z <= boxmax.z) &&
		(w >= boxmin.w) && (w <= boxmax.w)
		);
}

//-----------------------------------------------------------------------------
// Get the distance from this vector to the other one 
//-----------------------------------------------------------------------------
vec_t Vector4D::dist_to(const Vector4D& vOther) const {
	Vector4D delta;
	delta = *this - vOther;
	return delta.length();
}

//-----------------------------------------------------------------------------
// Returns a vector with the min or max in X, Y, and Z.
//-----------------------------------------------------------------------------
Vector4D Vector4D::Min(const Vector4D& vOther) const {
	return Vector4D(x < vOther.x ? x : vOther.x,
		y < vOther.y ? y : vOther.y,
		z < vOther.z ? z : vOther.z,
		w < vOther.w ? w : vOther.w);
}

Vector4D Vector4D::Max(const Vector4D& vOther) const {
	return Vector4D(x > vOther.x ? x : vOther.x,
		y > vOther.y ? y : vOther.y,
		z > vOther.z ? z : vOther.z,
		w > vOther.w ? w : vOther.w);
}


//-----------------------------------------------------------------------------
// arithmetic operations
//-----------------------------------------------------------------------------

Vector4D Vector4D::operator-(void) const {
	return Vector4D(-x, -y, -z, -w);
}

Vector4D Vector4D::operator+(const Vector4D& v) const {
	return Vector4D(x + v.x, y + v.y, z + v.z, w + v.w);
}

Vector4D Vector4D::operator-(const Vector4D& v) const {
	return Vector4D(x - v.x, y - v.y, z - v.z, w - v.w);
}

Vector4D Vector4D::operator*(float fl) const {
	return Vector4D(x * fl, y * fl, z * fl, w * fl);
}

Vector4D Vector4D::operator*(const Vector4D& v) const {
	return Vector4D(x * v.x, y * v.y, z * v.z, w * v.w);
}

Vector4D Vector4D::operator/(float fl) const {
	return Vector4D(x / fl, y / fl, z / fl, w / fl);
}

Vector4D Vector4D::operator/(const Vector4D& v) const {
	return Vector4D(x / v.x, y / v.y, z / v.z, w / v.w);
}

Vector4D operator*(float fl, const Vector4D& v) {
	return v * fl;
}