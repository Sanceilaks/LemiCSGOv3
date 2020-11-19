#pragma once
#include <game_sdk/interfaces/i_client_mode.h>
#include <game_sdk/misc/c_user_cmd.h>

namespace hooks
{
	struct create_move_hook
	{
		static const unsigned int index = 24;

		using fn = bool(__thiscall*)(IClientMode*, float, CUserCmd*);
		static bool __stdcall hook(float frame_time, CUserCmd* ucmd);

		static inline fn original;
		static inline void* target;
	};
}



class HooksManager
{
public:
	void init();
	void shutdown();
	
}; extern HooksManager* hooks_manager;