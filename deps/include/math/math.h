#pragma once

#include "vector.h" 

#ifndef LAPI
#define LAPI
#endif


namespace math
{
	static float PI_F = 3.14159265358979323846f;
	static double PI_D = 3.14159265358979323846;

	
	LAPI float rad2deg(float x);
	LAPI double rad2deg(double x);

	LAPI float deg2rad(float x);
	LAPI double deg2rad(double x);

	LAPI float procent(float var, float full);
	LAPI double procent(double var, double full);

	LAPI float float_negative(float var);
	LAPI double double_negative(double var);
	
}
