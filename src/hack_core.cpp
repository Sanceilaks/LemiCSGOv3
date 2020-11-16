#include "hack_core.h"
#include "interfaces.h"

bool hack_core::init()
{
	interfaces::init();
	return true;
}
