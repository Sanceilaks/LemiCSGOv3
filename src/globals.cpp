#include "globals.h"


namespace globals
{
	namespace view_matrix
	{
		bool has_offset = false;
		DWORD offset;
	}

	namespace ticks
	{
		int ticks_allowed = 0;
		int ticks_choke = 0;
		int next_tickbase_shift = 0;
		int tickbase_shift = 0;
		int fixed_tickbase = 0;
		int backup_tickbase = 0;
	}

	namespace view
	{
		CViewSetup last_setup;
	}
	
}
