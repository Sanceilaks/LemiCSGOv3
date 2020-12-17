#include "prediction_system.h"
#include <tools/mem_tools.h>
#include <game_sdk/entitys/entitys.h>

bool is_init = false;

PredictionSystem* prediction_system = new PredictionSystem();

void PredictionSystem::start(CUserCmd* ucmd)
{
	if (!is_init)
	{
		prediction_random_seed = *(int**)(mem_tools::pattern_scaner("client.dll", "8B 0D ? ? ? ? BA ? ? ? ? E8 ? ? ? ? 83 C4 04") + 2);
		is_init = true;
	}

	auto local_player = get_local_player();
	if (!local_player)
		return;
	
	*prediction_random_seed = ucmd->random_seed;

	old_curtime = interfaces->gvars->curtime;
	old_frametime = interfaces->gvars->frametime;

	interfaces->gvars->curtime = local_player->get_tick_base() * interfaces->gvars->interval_per_tick;
	interfaces->gvars->frametime = interfaces->gvars->interval_per_tick;

	interfaces->game_movement->start_track_prediction_errors(local_player);

	memset(&move_data, 0, sizeof(move_data));
	interfaces->move_helper->set_host(local_player);
	interfaces->prediction->setup_move(local_player, ucmd, interfaces->move_helper, &move_data);
	interfaces->game_movement->process_movement(local_player, &move_data);
	interfaces->prediction->finish_move(local_player, ucmd, &move_data);
}

void PredictionSystem::end()
{
	auto local_player = get_local_player();
	if (!local_player)
		return;
	
	interfaces->game_movement->finish_track_prediction_errors(local_player);
	interfaces->move_helper->set_host(0);

	*prediction_random_seed = -1;

	interfaces->gvars->curtime = old_curtime;
	interfaces->gvars->frametime = old_frametime;
}


