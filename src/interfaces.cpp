#include "interfaces.h"
#include <tools/mem_tools.h>

#include "logger.h"


Interfaces* interfaces = new Interfaces();

void Interfaces::init()
{
	engine = static_cast<IVEngineClient*>(mem_tools::capture_interface("engine.dll", "VEngineClient014"));
	entity_list = static_cast<VClientEntityList*>(mem_tools::capture_interface("client.dll", "VClientEntityList003"));
	debug_overlay = static_cast<VDebugOverlay*>(mem_tools::capture_interface("engine.dll", "VDebugOverlay004"));
	panel = static_cast<IPanel*>(mem_tools::capture_interface("vgui2.dll", "VGUI_Panel009"));
	client = static_cast<VBaseClient*>(mem_tools::capture_interface("client.dll", "VClient018"));
	cvar = static_cast<ICvar*>(mem_tools::capture_interface("vstdlib.dll", "VEngineCvar007"));
	surface = static_cast<ISurface*>(mem_tools::capture_interface("vguimatsurface.dll", "VGUI_Surface031"));
	engine_trace = static_cast<IEngineTrace*>(mem_tools::capture_interface("engine.dll", "EngineTraceClient004"));

	
	do { this->client_mode = **reinterpret_cast<IClientMode***>((*reinterpret_cast<uintptr_t**>(this->client))[10] + 0x5); } while (!this->client_mode);
	this->direct_device = **(IDirect3DDevice9***)(mem_tools::pattern_scaner("shaderapidx9.dll", "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 1);
}


void Interfaces::print_interfaces()
{
	logger::logf(logger::msg, "Engine -> %d", reinterpret_cast<int>(engine));
	logger::logf(logger::msg, "EntityList -> %d", reinterpret_cast<int>(entity_list));
	logger::logf(logger::msg, "DebugOverlay -> %d", reinterpret_cast<int>(debug_overlay));
	logger::logf(logger::msg, "Panel -> %d", reinterpret_cast<int>(panel));
	
}
