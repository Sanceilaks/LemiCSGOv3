#pragma once

#pragma region include_interfaces
#include "game_interfaces/engine_client.h"
#include "game_interfaces/v_client_entity_list.h"
#include "game_interfaces/v_debug_overlay.h"
#include "game_interfaces/i_panel.h"

#pragma endregion 



class interfaces
{
public:
	static IVEngineClient* engine;
	static VClientEntityList* entity_list;
	static VDebugOverlay* debug_overlay;
	static IPanel* panel;

	
	static void init();
	static void print_interfaces();
};