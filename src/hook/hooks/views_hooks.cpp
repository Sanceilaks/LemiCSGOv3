#include "../hooks_manager.h"
#include <interfaces.h>

#include <globals.h>
#include <settings/settings.h>

#include <game_sdk/entitys/entitys.h>

int old_fov, old_viewmodel_fov;
float old_ratio;


auto inited = false;
auto aspect_ration_changed = false;

auto init(CViewSetup* view)
{
	old_fov = view->fov;
	old_viewmodel_fov = view->viewmodel_fov;
	old_ratio = interfaces->cvar->find("r_aspectratio")->get_float();
	inited = true;
}



void __stdcall hooks::override_view_hook::hook(CViewSetup* view)
{
	if (!interfaces->engine->is_connected() || !interfaces->engine->is_in_game())
		return original(interfaces->client_mode, view);
	
	if (!globals::view_matrix::has_offset)
	{
		globals::view_matrix::has_offset = true;
		globals::view_matrix::offset = (reinterpret_cast<DWORD>(&interfaces->engine->world_to_screen_matrix()) + 0x40);
	}

	if (!inited)
	{
		init(view);
	}

	if (!view)
		return original(interfaces->client_mode, view);

	globals::view::last_setup = *view;
	
	auto local_player = get_local_player();

	if (local_player)
	{
		auto weapon = local_player->get_active_weapon();


		if (weapon)
		{
			if (settings::visuals::fov > 0)
			{
				if (!local_player->is_scoped())
					view->fov += (float)settings::visuals::fov;
				else
				{
					//if (weapon->get_zoom_level() == 1)
					//	view->fov = 90.0f + (float)settings::visuals::fov;
					//else
						view->fov += (float)settings::visuals::fov;
				}
			}
		}
		else if (settings::visuals::fov > 0)
			view->fov += settings::visuals::fov;
	}

	if (settings::visuals::override_aspect_ratio)
	{
		if (settings::visuals::aspect_ratio > 0)
		{
			float ratio = (settings::visuals::aspect_ratio * 0.1f) * 0.5f;

			if (ratio > 0.001f)
				interfaces->cvar->find("r_aspectratio")->set_value(ratio);
			else
				interfaces->cvar->find("r_aspectratio")->set_value((35 * 0.1f) * 0.5f);

			aspect_ration_changed = true;
		}
		else
		{
			interfaces->cvar->find("r_aspectratio")->set_value(old_ratio);
		}
	}
	else if (aspect_ration_changed)
	{
		interfaces->cvar->find("r_aspectratio")->set_value(old_ratio);
		aspect_ration_changed = false;
	}
	
	original(interfaces->client_mode, view);
}
