#include "hack_core.h"
#include "interfaces.h"
#include "hook/hooks_manager.h"
#include <game_sdk/misc/color.h>
HackCore* hack_core = new HackCore();

bool HackCore::init()
{
	interfaces->init();
	interfaces->engine->execute_client_cmd("clear");
	interfaces->cvar->console_color_printf(Color(0, 255, 0), "interfaces::init ok\n");
	//interfaces->print_interfaces();

	hooks_manager->init();
	interfaces->cvar->console_color_printf(Color(0, 255, 0), "hooks_manager::init ok\n");
	
	
	return true;
}
