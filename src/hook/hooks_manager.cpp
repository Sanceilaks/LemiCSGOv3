#include "hooks_manager.h"

#include <minhook/minhook.h> 
#include <logger.h>

HooksManager* hooks_manager = new HooksManager();


void HooksManager::init()
{
	if (MH_Initialize() != MH_OK)
	{
		throw std::exception("Fail to  hooks_manager::init! Pls contact with developer!");
	}


	MH_EnableHook(MH_ALL_HOOKS);
}
