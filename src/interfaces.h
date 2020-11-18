#pragma once

#pragma region include_interfaces
#include "game_interfaces/engine_client.h"
#include "game_interfaces/v_client_entity_list.h"
#include "game_interfaces/v_debug_overlay.h"
#include "game_interfaces/i_panel.h"

#pragma endregion 



class Interfaces
{
public:
	IVEngineClient* engine;
	VClientEntityList* entity_list;
	VDebugOverlay* debug_overlay;
	IPanel* panel;

	
	void init();
	void print_interfaces();
}; extern Interfaces* interfaces;