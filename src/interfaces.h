#pragma once

#pragma region include_interfaces
#include "game_sdk/interfaces/i_material_system.h"
#include "game_sdk/interfaces/engine_client.h"
#include "game_sdk/interfaces/v_client_entity_list.h"
#include "game_sdk/interfaces/v_debug_overlay.h"
#include "game_sdk/interfaces/i_panel.h"
#include "game_sdk/interfaces/i_client_mode.h"
#include "game_sdk/interfaces/v_base_client.h"
#include "game_sdk/interfaces/i_cvar.h"
#include "game_sdk/interfaces/i_surface.h"
#include "game_sdk/interfaces/i_engine_trace.h"
#include "game_sdk/interfaces/c_global_vars.h"
#include "game_sdk/interfaces/i_game_movement.h"
#include "game_sdk/interfaces/i_move_helper.h"
#include "game_sdk/interfaces/i_prediction.h"
#include "game_sdk/interfaces/iv_model_render.h"
#include <d3d9.h>

#pragma endregion 



class Interfaces
{
public:
	IVEngineClient* engine;
	VClientEntityList* entity_list;
	VDebugOverlay* debug_overlay;
	IPanel* panel;
	IClientMode* client_mode;
	VBaseClient* client;
	ICvar* cvar;
	IDirect3DDevice9* direct_device;
	ISurface* surface;
	IEngineTrace* engine_trace;
	CGlobalVars* gvars;
	IGameMovement* game_movement;
	IMoveHelper* move_helper;
	IPrediction* prediction;
	IMaterialSystem* material_system;
	IVModelRender* model_render;
	
	void init();
	void print_interfaces();
}; extern Interfaces* interfaces;