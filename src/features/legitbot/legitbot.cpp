#include "legitbot.h"

LegitBot* legit_bot = new LegitBot();

auto LegitBot::get_target(CUserCmd* cmd) -> CBasePlayer*
{
	CBasePlayer* local_player = get_local_player();

	if (!local_player)
		return nullptr;
	
	float BEST_FOV = FLT_MAX;
	CBasePlayer* target = nullptr;
	
	for (size_t i = 0; i <= interfaces->gvars->max_clients; ++i)
	{
		auto ply = get_player_by_index(i);

		if (!player_valid(ply))
			continue;

		Vector engine_angles;
		interfaces->engine->get_viewangles(engine_angles);
		float fov = math::get_fov(engine_angles, math::calc_angle(local_player->get_eye_pos(), ply->get_entity_bone(Bones::HEAD_0)));

		if (fov < BEST_FOV)
		{
			BEST_FOV = fov;
			target = ply;
		}
	}

	return target;
}

void LegitBot::run(CUserCmd* cmd)
{
	if (!interfaces->engine->is_in_game())
		return;

	CBasePlayer* local_player = get_local_player();

	if (!local_player || !local_player->is_alive())
		return;

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		auto target = get_target(cmd);
		if (target == nullptr)
			return;
		
		if (player_valid(target, false))
		{
			auto angle = math::calc_angle(local_player->get_eye_pos(), target->get_eye_pos());

			cmd->viewangles = angle;
			interfaces->engine->set_viewangles(angle);

		}
	}
}
