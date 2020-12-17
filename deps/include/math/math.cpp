#include "math.h"


//#include <Windows.h>
#include <excpt.h>
#include <d3dx9.h>
#include <D3dx9math.h>
#include <DirectXMath.h>

#include <interfaces.h>

#include "globals.h"

float math::rad2deg(float x)
{
    return x * (180.f / PI_F);
}

double math::rad2deg(double x)
{
	return x * (static_cast<double>(180.0) / PI_D);
}

float math::deg2rad(float x)
{
	return x * (PI_F / 180.f);
}

double math::deg2rad(double x)
{
	return x * (PI_D / static_cast<double>(180.0));
}

float math::procent(float var, float full)
{
	return 100.f / full * var;
}

double math::procent(double var, double full)
{
	return 100.0 / full * var;
}

float math::float_negative(float var)
{
	return -var;
}

double math::double_negative(double var)
{
	return -var;
}

bool math::world_to_screen(const Vector& in, Vector& out)
{
	if (!globals::view_matrix::has_offset)
		return false;

	if (!screen_transform(in, out))
		return false;

	int w, h;
	interfaces->engine->get_screen_size(w, h);
	
	out.x = (w / 2.0f) + (out.x * w) / 2.0f;
	out.y = (h / 2.0f) - (out.y * h) / 2.0f;

	return true;
}

bool math::screen_transform(const Vector& in, Vector& out)	//pasted from Sensum aka Indigo
{
	auto exception_filter = [](int code, PEXCEPTION_POINTERS ex)
	{
		return EXCEPTION_EXECUTE_HANDLER;
	};

	__try
	{
		auto result = *(PDWORD)(globals::view_matrix::offset) + 988;
		if (!result)
		{
			out.x *= 100000;
			out.y *= 100000;
			return false;
		}

		const auto& world_matrix = *(_D3DMATRIX*)result;

		const auto w = world_matrix.m[3][0] * in.x + world_matrix.m[3][1] * in.y + world_matrix.m[3][2] * in.z + world_matrix.m[3][3];
		if (w < 0.001f)
		{
			out.x *= 100000;
			out.y *= 100000;
			return false;
		}

		out.x = world_matrix.m[0][0] * in.x + world_matrix.m[0][1] * in.y + world_matrix.m[0][2] * in.z + world_matrix.m[0][3];
		out.y = world_matrix.m[1][0] * in.x + world_matrix.m[1][1] * in.y + world_matrix.m[1][2] * in.z + world_matrix.m[1][3];
		out.z = 0.0f;

		out.x /= w;
		out.y /= w;

		return true;
	}
	__except (exception_filter(GetExceptionCode(), GetExceptionInformation()))
	{
		out.x *= 100000;
		out.y *= 100000;
		return false;
	}
}

void math::normalize_angles(Vector& angles)
{
	while (angles.x > 89.0f)
		angles.x -= 180.0f;

	while (angles.x < -89.0f)
		angles.x += 180.0f;

	while (angles.y < -180.0f)
		angles.y += 360.0f;

	while (angles.y > 180.0f)
		angles.y -= 360.0f;

	angles.z = 0.0f;
}

Vector math::calc_angle(const Vector& from, const Vector& to)
{
	Vector angles;

	Vector delta = from - to;
	float hyp = delta.length2d();

	angles.y = std::atanf(delta.y / delta.x) * 57.295779513082f; //Magic number
	angles.x = std::atanf(-delta.z / hyp) * - 57.295779513082f;
	angles.z = 0.0f;

	if (delta.x >= 0.0f)
		angles.y += 180.0f;

	return angles;
}

float math::get_fov(const Vector& from, const Vector& to)
{
	Vector delta = to - from;
	normalize_angles(delta);
	return sqrtf(powf(delta.x, 2.f) + powf(delta.y, 2.f));
}
