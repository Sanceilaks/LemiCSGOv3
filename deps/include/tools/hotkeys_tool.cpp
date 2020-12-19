#include "hotkeys_tool.h"

#define KEYS_NUM 165

bool* keys_state;
UINT* frames;
UINT current_frame;

void hotkeys_tool::init()
{
	keys_state = new bool[KEYS_NUM];
	frames = new UINT[KEYS_NUM];

	memset(keys_state, false, KEYS_NUM * sizeof(bool));
	memset(frames, 0, KEYS_NUM * sizeof(UINT));
	
}

void hotkeys_tool::on_key_down(int code)
{
	if (!(code > KEYS_NUM))
	{
		keys_state[code] = true;
	}
}

void hotkeys_tool::on_key_up(int code)
{
	if (!(code > KEYS_NUM))
	{
		keys_state[code] = false;
	}
}

void hotkeys_tool::on_mouse_move(double x, double y)
{
}

bool hotkeys_tool::is_key_pressed(int code)
{
	if (code <= KEYS_NUM)
		return keys_state[code];
	return false;
}

bool hotkeys_tool::is_key_up(int code)
{
	if (code <= KEYS_NUM)
		return !keys_state[code];
	return false;
}
