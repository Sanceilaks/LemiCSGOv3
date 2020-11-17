#pragma once
#include <math/vector.h>

class VDebugOverlay
{
public:
	bool world_to_screen(const Vector& in, Vector& out) {
		using original_fn = int(__thiscall*)(VDebugOverlay*, const Vector&, Vector&);
		int return_value = (*(original_fn**)this)[13](this, in, out);
		return static_cast<bool>(return_value != 1);
	}	

};