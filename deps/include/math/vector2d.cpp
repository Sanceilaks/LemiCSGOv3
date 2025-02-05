#include "vector2d.h"
#include <cmath>


Vector2D::Vector2D(void) {
}

Vector2D::Vector2D(vec_t X, vec_t Y) {
	x = X; y = Y;
}

Vector2D::Vector2D(vec_t* clr) {
	x = clr[0]; y = clr[1];
}

//-----------------------------------------------------------------------------
// initialization
//-----------------------------------------------------------------------------

void Vector2D::init(vec_t ix, vec_t iy) {
	x = ix; y = iy;
}

void Vector2D::random(float minVal, float maxVal) {
	x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
}

void CVector2DClear(Vector2D& a) {
	a.x = a.y = 0.0f;
}

//-----------------------------------------------------------------------------
// assignment
//-----------------------------------------------------------------------------

Vector2D& Vector2D::operator=(const Vector2D& vOther) {
	x = vOther.x; y = vOther.y;
	return *this;
}

//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------

vec_t& Vector2D::operator[](int i) {
	return ((vec_t*)this)[i];
}

vec_t Vector2D::operator[](int i) const {
	return ((vec_t*)this)[i];
}

//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------

vec_t* Vector2D::Base() {
	return (vec_t*)this;
}

vec_t const* Vector2D::base() const {
	return (vec_t const*)this;
}

//-----------------------------------------------------------------------------
// IsValid?
//-----------------------------------------------------------------------------

bool Vector2D::is_valid() const {
	return !isinf(x) && !isinf(y);
}

//-----------------------------------------------------------------------------
// comparison
//-----------------------------------------------------------------------------

bool Vector2D::operator==(const Vector2D& src) const {
	return (src.x == x) && (src.y == y);
}

bool Vector2D::operator!=(const Vector2D& src) const {
	return (src.x != x) || (src.y != y);
}


//-----------------------------------------------------------------------------
// Copy
//-----------------------------------------------------------------------------

void CVector2DCopy(const Vector2D& src, Vector2D& dst) {
	dst.x = src.x;
	dst.y = src.y;
}

void	Vector2D::copy_to_array(float* rgfl) const {
	rgfl[0] = x; rgfl[1] = y;
}

//-----------------------------------------------------------------------------
// standard math operations
//-----------------------------------------------------------------------------

void Vector2D::negate() {
	x = -x; y = -y;
}

void CVector2DAdd(const Vector2D& a, const Vector2D& b, Vector2D& c) {
	c.x = a.x + b.x;
	c.y = a.y + b.y;
}

void CVector2DSubtract(const Vector2D& a, const Vector2D& b, Vector2D& c) {
	c.x = a.x - b.x;
	c.y = a.y - b.y;
}

void CVector2DMultiply(const Vector2D& a, vec_t b, Vector2D& c) {
	c.x = a.x * b;
	c.y = a.y * b;
}

void CVector2DMultiply(const Vector2D& a, const Vector2D& b, Vector2D& c) {
	c.x = a.x * b.x;
	c.y = a.y * b.y;
}


void CVector2DDivide(const Vector2D& a, vec_t b, Vector2D& c) {
	vec_t oob = 1.0f / b;
	c.x = a.x * oob;
	c.y = a.y * oob;
}

void CVector2DDivide(const Vector2D& a, const Vector2D& b, Vector2D& c) {
	c.x = a.x / b.x;
	c.y = a.y / b.y;
}

void CVector2DMA(const Vector2D& start, float s, const Vector2D& dir, Vector2D& result) {
	result.x = start.x + s * dir.x;
	result.y = start.y + s * dir.y;
}

// FIXME: Remove
// For backwards compatability
void	Vector2D::mul_add(const Vector2D& a, const Vector2D& b, float scalar) {
	x = a.x + b.x * scalar;
	y = a.y + b.y * scalar;
}

void CVector2DLerp(const Vector2D& src1, const Vector2D& src2, vec_t t, Vector2D& dest) {
	dest[0] = src1[0] + (src2[0] - src1[0]) * t;
	dest[1] = src1[1] + (src2[1] - src1[1]) * t;
}

//-----------------------------------------------------------------------------
// dot, cross
//-----------------------------------------------------------------------------
vec_t DotProduct2D(const Vector2D& a, const Vector2D& b) {
	return(a.x * b.x + a.y * b.y);
}

// for backwards compatability
vec_t Vector2D::dot(const Vector2D& vOther) const {
	return DotProduct2D(*this, vOther);
}

vec_t CVector2DNormalize(Vector2D& v) {
	vec_t l = v.length();
	if (l != 0.0f) {
		v /= l;
	}
	else {
		v.x = v.y = 0.0f;
	}
	return l;
}

//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------
vec_t CVector2DLength(const Vector2D& v) {
	return (vec_t)sqrt(v.x * v.x + v.y * v.y);
}

vec_t Vector2D::normalize_in_place() {
	return CVector2DNormalize(*this);
}

bool Vector2D::is_length_greater_than(float val) const {
	return length_sqr() > val * val;
}

bool Vector2D::is_length_less_than(float val) const {
	return length_sqr() < val * val;
}

vec_t Vector2D::length(void) const {
	return CVector2DLength(*this);
}


void CVector2DMin(const Vector2D& a, const Vector2D& b, Vector2D& result) {
	result.x = (a.x < b.x) ? a.x : b.x;
	result.y = (a.y < b.y) ? a.y : b.y;
}


void CVector2DMax(const Vector2D& a, const Vector2D& b, Vector2D& result) {
	result.x = (a.x > b.x) ? a.x : b.x;
	result.y = (a.y > b.y) ? a.y : b.y;
}

//-----------------------------------------------------------------------------
// Computes the closest point to vecTarget no farther than flMaxDist from vecStart
//-----------------------------------------------------------------------------
void ComputeClosestPoint2D(const Vector2D& vecStart, float flMaxDist, const Vector2D& vecTarget, Vector2D* pResult) {
	Vector2D vecDelta;
	CVector2DSubtract(vecTarget, vecStart, vecDelta);
	float flDistSqr = vecDelta.length_sqr();
	if (flDistSqr <= flMaxDist * flMaxDist) {
		*pResult = vecTarget;
	}
	else {
		vecDelta /= sqrt(flDistSqr);
		CVector2DMA(vecStart, flMaxDist, vecDelta, *pResult);
	}
}

//-----------------------------------------------------------------------------
// Returns a CVector2D with the min or max in X, Y, and Z.
//-----------------------------------------------------------------------------

Vector2D Vector2D::get_min(const Vector2D& vOther) const {
	return Vector2D(x < vOther.x ? x : vOther.x, y < vOther.y ? y : vOther.y);
}

Vector2D Vector2D::get_max(const Vector2D& vOther) const {
	return Vector2D(x > vOther.x ? x : vOther.x, y > vOther.y ? y : vOther.y);
}


//-----------------------------------------------------------------------------
// arithmetic operations
//-----------------------------------------------------------------------------

Vector2D Vector2D::operator-(void) const {
	return Vector2D(-x, -y);
}

Vector2D Vector2D::operator+(const Vector2D& v) const {
	Vector2D res;
	CVector2DAdd(*this, v, res);
	return res;
}

Vector2D Vector2D::operator-(const Vector2D& v) const {
	Vector2D res;
	CVector2DSubtract(*this, v, res);
	return res;
}

Vector2D Vector2D::operator*(float fl) const {
	Vector2D res;
	CVector2DMultiply(*this, fl, res);
	return res;
}

Vector2D Vector2D::operator*(const Vector2D& v) const {
	Vector2D res;
	CVector2DMultiply(*this, v, res);
	return res;
}

Vector2D Vector2D::operator/(float fl) const {
	Vector2D res;
	CVector2DDivide(*this, fl, res);
	return res;
}

Vector2D Vector2D::operator/(const Vector2D& v) const {
	Vector2D res;
	CVector2DDivide(*this, v, res);
	return res;
}

Vector2D operator*(float fl, const Vector2D& v) {
	return v * fl;
}