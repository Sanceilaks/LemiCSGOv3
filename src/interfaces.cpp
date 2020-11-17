#include "interfaces.h"
#include <tools/mem_tools.h>


IVEngineClient* interfaces::engine;
VClientEntityList* interfaces::entity_list;
VDebugOverlay* interfaces::debug_overlay;
IPanel* interfaces::panel;

void interfaces::init()
{
	engine = static_cast<IVEngineClient*>(mem_tools::capture_interface("engine.dll", "VEngineClient014"));
	entity_list = static_cast<VClientEntityList*>(mem_tools::capture_interface("client.dll", "VClientEntityList003"));
	debug_overlay = static_cast<VDebugOverlay*>(mem_tools::capture_interface("engine.dll", "VDebugOverlay004"));
	panel = static_cast<IPanel*>(mem_tools::capture_interface("vgui2.dll", "VGUI_Panel009"));
	
}


void interfaces::print_interfaces()
{

}