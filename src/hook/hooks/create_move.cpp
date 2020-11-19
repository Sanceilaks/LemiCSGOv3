#include <Windows.h>

#include "../hooks_manager.h"
#include <interfaces.h>

#include <math/math.h>

#include "game_sdk/entitys/c_base_player.h"


bool __stdcall hooks::create_move_hook::hook(float frame_time, CUserCmd* ucmd)
{
	if (!ucmd || !ucmd->command_number)
		return hooks::create_move_hook::original(interfaces->client_mode, frame_time, ucmd);

	DWORD move;
	_asm mov move, ebp;
	bool& sendpacket = *(***(bool****)(move)-1);

	auto local_player = get_local_player();

	if (!local_player)
		return false;

	///	Todo: Improve bhop
	if (ucmd->buttons & IN_JUMP && !(local_player->get_flags() & static_cast<int>(FL_ONGROUND)))
		ucmd->buttons &= ~IN_JUMP;
	
	return false;
}
