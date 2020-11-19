#include <Windows.h>

#include "../hooks_manager.h"
#include <interfaces.h>

#include <math/math.h>

bool __stdcall hooks::create_move_hook::hook(float frame_time, CUserCmd* ucmd)
{
	if (!ucmd || !ucmd->command_number)
		return hooks::create_move_hook::original(interfaces->client_mode, frame_time, ucmd);

	DWORD move;
	_asm mov move, ebp;
	bool& sendpacket = *(***(bool****)(move)-1);

	if (ucmd->buttons & IN_JUMP)
		ucmd->buttons &= ~IN_JUMP;
	
	return false;
}
