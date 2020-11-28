#pragma once
#include <Windows.h>

#include "vector2d.h"
#include "vector3d.h"
#include "vector4d.h"
#include "qangle.h"


class __declspec(align(16)) VectorAligned : public Vector {
public:
	inline VectorAligned(void) {};
	inline VectorAligned(vec_t X, vec_t Y, vec_t Z) {
		init(X, Y, Z);
	}

public:
	explicit VectorAligned(const Vector& vOther) {
		init(vOther.x, vOther.y, vOther.z);
	}

	VectorAligned& operator=(const Vector& vOther) {
		init(vOther.x, vOther.y, vOther.z);
		return *this;
	}

	//CVectorAligned& operator=(const CVectorAligned& vOther) {
	//	_mm_store_ps(Base(), _mm_load_ps(vOther.Base()));
	//	return *this;
	//}

	float w;
};
FORCEINLINE void VectorSubtract(const Vector& a, const Vector& b, Vector& c)
{
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
}
FORCEINLINE void VectorAdd(const Vector& a, const Vector& b, Vector& c)
{
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
}
