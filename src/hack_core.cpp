#include "hack_core.h"
#include "interfaces.h"


HackCore* hack_core = new HackCore();

bool HackCore::init()
{
	interfaces->init();
	return true;
}
