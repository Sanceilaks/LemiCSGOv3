#include "interfaces.h"
#include <tools/mem_tools.h>


Interfaces* interfaces = new Interfaces();

void Interfaces::init()
{
	engine = static_cast<IVEngineClient*>(mem_tools::capture_interface("engine.dll", "VEngineClient014"));
	entity_list = static_cast<VClientEntityList*>(mem_tools::capture_interface("client.dll", "VClientEntityList003"));
	debug_overlay = static_cast<VDebugOverlay*>(mem_tools::capture_interface("engine.dll", "VDebugOverlay004"));
	panel = static_cast<IPanel*>(mem_tools::capture_interface("vgui2.dll", "VGUI_Panel009"));
	
}


void Interfaces::print_interfaces()
{

}