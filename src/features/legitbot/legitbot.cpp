#include "legitbot.h"
#include <settings/settings.h>
#include <tools/hotkeys_tool.h>

LegitBot* legit_bot = new LegitBot();

auto LegitBot::get_target(CUserCmd* cmd) -> CBasePlayer*
{
	CBasePlayer* local_player = get_local_player();

	if (!local_player)
		return nullptr;
	
	float BEST_FOV = FLT_MAX;
	CBasePlayer* t = nullptr;
	
	for (size_t i = 0; i <= interfaces->gvars->max_clients; ++i)
	{
		auto ply = get_player_by_index(i);

		if (!player_valid(ply, true, true))
			continue;

		Vector engine_angles;
		interfaces->engine->get_viewangles(engine_angles);
		float fov = math::get_fov(engine_angles, math::calc_angle(local_player->get_eye_pos(), ply->get_entity_bone(8)) - local_player->get_aim_punch() * 2);

		if (fov < BEST_FOV && fov <= settings::legit_bot::fov)
		{
			BEST_FOV = fov;
			t = ply;
		}
	}

	return t;
}

void LegitBot::run(CUserCmd* cmd)
{
	if (!interfaces->engine->is_in_game())
		return;

	CBasePlayer* local_player = get_local_player();
	
	if (!local_player || !local_player->is_alive())
		return;
	
	auto weapon = local_player->get_active_weapon();

	if (!weapon || !weapon->can_fire(true))
		return;

	CBasePlayer* target = nullptr;
	
	if (settings::legit_bot::enable && (!(cmd->buttons & IN_ATTACK) || !target))
		target = get_target(cmd);
	
	if (target == nullptr)
		return;
	
	if (GetAsyncKeyState(settings::legit_bot::aim_key) || !settings::legit_bot::aim_key || (settings::legit_bot::auto_fire && (GetAsyncKeyState(settings::legit_bot::auto_fire_key) || !settings::legit_bot::auto_fire_key)))
	{		
		if (player_valid(target, true, true))
		{
			auto bone = target->get_entity_bone(6);
			auto angle = math::calc_angle(local_player->get_eye_pos(), target->get_entity_bone(8)) - local_player->get_aim_punch() * 2;

			cmd->viewangles = angle;
			interfaces->engine->set_viewangles(angle);

			if (settings::legit_bot::auto_fire)
				if (GetAsyncKeyState(settings::legit_bot::auto_fire_key) || !settings::legit_bot::auto_fire_key)
					cmd->buttons |= IN_ATTACK;
		}
		else
		{
			target = nullptr;
		}
	}
}
