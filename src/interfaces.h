#pragma once

#pragma region include_interfaces
#include "game_interfaces/engine_client.h"

#pragma endregion 



class interfaces
{
public:
	static IVEngineClient* engine;
	
	static void init();
	static void print_interfaces();
};