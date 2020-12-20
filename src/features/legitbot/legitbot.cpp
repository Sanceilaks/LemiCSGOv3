#include "legitbot.h"
#include <settings/settings.h>
#include <tools/hotkeys_tool.h>
#include <features/aim_step/aim_step.h>

LegitBot* legit_bot = new LegitBot();

bool do_smooth(float smooth, const Vector& from, const Vector& to, Vector& out)
{
	auto tickrate = 1.f / interfaces->gvars->interval_per_tick;
	if (tickrate != 64.f)
	{
		smooth = tickrate * smooth / 64.f;
	}

	if (smooth < 1.1f)
	{
		out = to;
		return true;
	}

	auto delta = to - from;
	math::normalize_angles(delta);
	
	auto to_out = from + delta / smooth;
	math::normalize_angles(to_out);

	out = to_out;

	return roundf(out.x) == roundf(to.x) && roundf(out.y) == roundf(to.y);
}

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
		float fov = math::get_fov(engine_angles, math::calc_angle(local_player->get_eye_pos(), ply->get_entity_bone(BONE_HEAD)) + local_player->get_aim_punch() * 2);

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

	if (!settings::legit_bot::enable)
		return;
	
	CBasePlayer* local_player = get_local_player();
	
	if (!local_player || !local_player->is_alive())
		return;
	
	auto weapon = local_player->get_active_weapon();

	if (!weapon || !weapon->can_fire(true))
		return;
	
	if (GetAsyncKeyState(settings::legit_bot::aim_key) || !settings::legit_bot::aim_key || (settings::legit_bot::auto_fire && (GetAsyncKeyState(settings::legit_bot::auto_fire_key) || !settings::legit_bot::auto_fire_key)))
	{
		CBasePlayer* target = nullptr;

		if (settings::legit_bot::enable && !target)
			target = get_target(cmd);

		if (target == nullptr)
			return;
		
		if (player_valid(target, true, true))
		{
			auto angle = math::calc_angle(local_player->get_eye_pos(), target->get_entity_bone(BONE_HEAD));
			auto to_ang = angle;
			angle = angle - (settings::legit_bot::rcs_enable ? local_player->get_aim_punch() * settings::legit_bot::rcs_factor : Vector(0, 0, 0));
			
			auto smooth_finish = do_smooth(settings::legit_bot::smooth, cmd->viewangles, to_ang, angle);
			
			auto step_finish = settings::legit_bot::aim_step ? aim_step->run(cmd->viewangles, angle, angle) : true;
			
			cmd->viewangles = angle;
			interfaces->engine->set_viewangles(angle);

			if (settings::legit_bot::auto_fire)
				if ((GetAsyncKeyState(settings::legit_bot::auto_fire_key) || !settings::legit_bot::auto_fire_key) && (smooth_finish && step_finish))
					cmd->buttons |= IN_ATTACK;
		}
	}
}
