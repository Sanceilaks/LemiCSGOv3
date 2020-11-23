#pragma once

#include "vector.h"
#include "vmatrix.h"
#include <algorithm>

#ifndef LAPI
#define LAPI
#endif


namespace math
{
	struct box
	{
		float x, y, w, h;
		box() = default;
		box(float x, float y, float w, float h)
		{
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}
	};
	
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

	template< typename t = float >
	LAPI void clamp(t& val, t& min, t& max) {
		// check type.
		static_assert(std::is_arithmetic< t >::value, "clamp only integral types.");
		val = (t)_mm_cvtss_f32(
			_mm_min_ss(_mm_max_ss(_mm_set_ss((float)val), _mm_set_ss((float)min)),
				_mm_set_ss((float)max))
		);
	}

	template < typename t >
	LAPI t fclamp(t in, t low, t high)
	{
		#ifdef min
		#undef min;
		#endif
		#ifdef max
		#undef max;
		#endif
		return std::min(std::max(in, low), high);
	}

	bool world_to_screen(const Vector& in, Vector& out);
	bool screen_transform(const Vector& in, Vector& out);
}
