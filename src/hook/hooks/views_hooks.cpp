#include "../hooks_manager.h"
#include <interfaces.h>

#include <globals.h>

void __stdcall hooks::override_view_hook::hook(CViewSetup* view)
{
	if (!interfaces->engine->is_connected() || !interfaces->engine->is_in_game())
		return original(interfaces->client_mode, view);

	if (!globals::view_matrix::has_offset)
	{
		globals::view_matrix::has_offset = true;
		globals::view_matrix::offset = (reinterpret_cast<DWORD>(&interfaces->engine->world_to_screen_matrix()) + 0x40);
	}

	original(interfaces->client_mode, view);
}
