#include "hooks_manager.h"

#include <minhook/minhook.h> 
#include <logger.h>
#include <interfaces.h>

HooksManager* hooks_manager = new HooksManager();

inline unsigned int get_virtual(void* _class, unsigned int index) { return static_cast<unsigned int>((*static_cast<int**>(_class))[index]); }


void HooksManager::init()
{
	hooks::create_move_hook::target = reinterpret_cast<void*>(get_virtual(interfaces->client_mode, hooks::create_move_hook::index));

	
	if (MH_Initialize() != MH_OK)
	{
		throw std::exception("Failed to  hooks_manager::init! Pls contact with developer!");
	}

	if ( MH_CreateHook(hooks::create_move_hook::target, &hooks::create_move_hook::hook, reinterpret_cast<void**>(&hooks::create_move_hook::original)) != MH_OK)
	{
		throw std::exception("Failed to hook create_move");
	}

	
	MH_EnableHook(MH_ALL_HOOKS);
}

void HooksManager::shutdown()
{
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}
