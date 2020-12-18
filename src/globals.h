#pragma once
#include <Windows.h>
#include <game_sdk/misc/c_view_setup.h>

namespace globals
{
	
	namespace view_matrix
	{
		extern bool has_offset;
		extern DWORD offset;
	}

	namespace ticks
	{
		extern int ticks_allowed;
		extern int ticks_choke;
		extern int next_tickbase_shift;
		extern int tickbase_shift;
		extern int fixed_tickbase;
		extern int backup_tickbase;
	}

	namespace view
	{
		extern CViewSetup last_setup;
	}
	
}
