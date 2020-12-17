#pragma once

#define NOMINMAX
#include <Windows.h>
#include <cstdint>
#include <functional>

#ifndef LAPI
#define LAPI
#endif


namespace hotkeys_tool
{
	enum key_state
	{
		none = 1,
		down,
		up,
		pressed
	};

	DEFINE_ENUM_FLAG_OPERATORS(key_state);
	
	void init();

	
	key_state get_key_state(int key);
	void set_key_state(int key, bool state);
	
}
