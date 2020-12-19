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
	LAPI void init();
	
	LAPI void on_key_down(int code);
	LAPI void on_key_up(int code);
	
	
	LAPI void on_mouse_move(double x, double y);

	LAPI bool is_key_pressed(int code);
	LAPI bool is_key_up(int code);
	
}
