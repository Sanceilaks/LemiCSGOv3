#include "hack_core.h"
#include "interfaces.h"
#include "hook/hooks_manager.h"

HackCore* hack_core = new HackCore();

bool HackCore::init()
{
	interfaces->init();
	//interfaces->print_interfaces();

	hooks_manager->init();
	
	return true;
}
