#include "hooks_manager.h"

#include <minhook/minhook.h> 
#include <logger.h>
#include <interfaces.h>

HooksManager* hooks_manager = new HooksManager();

inline unsigned int get_virtual(void* _class, unsigned int index) { return static_cast<unsigned int>((*static_cast<int**>(_class))[index]); }


void HooksManager::init()
{
	hooks::create_move_hook::target = reinterpret_cast<void*>(get_virtual(interfaces->client_mode, hooks::create_move_hook::index));
	hooks::end_scane_hook::target = reinterpret_cast<void*>(get_virtual(interfaces->direct_device, hooks::end_scane_hook::index));
	hooks::reset_hook::target = reinterpret_cast<void*>(get_virtual(interfaces->direct_device, hooks::reset_hook::index));
	hooks::override_view_hook::target = reinterpret_cast<void*>(get_virtual(interfaces->client_mode, hooks::override_view_hook::index));
	hooks::lock_cursor_hook::target = reinterpret_cast<void*>(get_virtual(interfaces->surface, hooks::lock_cursor_hook::index));
	hooks::draw_model_execute::target = reinterpret_cast<void*>(get_virtual(interfaces->model_render, hooks::draw_model_execute::index));
	
	if (MH_Initialize() != MH_OK)
	{
		throw std::exception("Failed to  hooks_manager::init! Pls contact with developer!");
	}

	if ( MH_CreateHook(hooks::create_move_hook::target, &hooks::create_move_hook::hook, reinterpret_cast<void**>(&hooks::create_move_hook::original)) != MH_OK)
	{
		throw std::exception("Failed to hook create_move");
	}

	if (MH_CreateHook(hooks::end_scane_hook::target, &hooks::end_scane_hook::hook, reinterpret_cast<void**>(&hooks::end_scane_hook::original)) != MH_OK)
	{
		throw std::exception("Failed to hook end_scane_hook");
	}

	if (MH_CreateHook(hooks::reset_hook::target, &hooks::reset_hook::hook, reinterpret_cast<void**>(&hooks::reset_hook::original)) != MH_OK)
	{
		throw std::exception("Failed to hook reset_hook");
	}

	if (MH_CreateHook(hooks::override_view_hook::target, &hooks::override_view_hook::hook, reinterpret_cast<void**>(&hooks::override_view_hook::original)) != MH_OK)
	{
		throw std::exception("Failed to hook override_view_hook");
	}

	if (MH_CreateHook(hooks::lock_cursor_hook::target, &hooks::lock_cursor_hook::hook, reinterpret_cast<void**>(&hooks::lock_cursor_hook::original)) != MH_OK)
	{
		throw std::exception("Failed to hook lock_cursor_hook");
	}

	if (MH_CreateHook(hooks::draw_model_execute::target, &hooks::draw_model_execute::hook, reinterpret_cast<void**>(&hooks::draw_model_execute::original)) != MH_OK)
	{
		throw std::exception("Failed to hook draw_model_execute");
	}
	
	MH_EnableHook(MH_ALL_HOOKS);
}

void HooksManager::shutdown()
{
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}
