#include "../hooks_manager.h"
#include <interfaces.h>

#include <globals.h>
#include <settings/settings.h>

static int old_fov, old_viewmodel_fov;

void __stdcall hooks::override_view_hook::hook(CViewSetup* view)
{
	if (!interfaces->engine->is_connected() || !interfaces->engine->is_in_game())
		return original(interfaces->client_mode, view);

	if (!globals::view_matrix::has_offset)
	{
		globals::view_matrix::has_offset = true;
		globals::view_matrix::offset = (reinterpret_cast<DWORD>(&interfaces->engine->world_to_screen_matrix()) + 0x40);
	}

	if (settings::visuals::fov == 0)
	{
		old_fov = view->fov;
		old_viewmodel_fov = view->viewmodel_fov;
		
		settings::visuals::fov = view->fov;
		//settings::visuals::viewmodel_fov = view->viewmodel_fov;
	}

	//view->viewmodel_fov = settings::visuals::viewmodel_fov;
	view->fov = settings::visuals::fov;
	
	original(interfaces->client_mode, view);
}
