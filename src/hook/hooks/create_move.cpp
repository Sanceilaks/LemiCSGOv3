#include <Windows.h>

#include "../hooks_manager.h"
#include <interfaces.h>

#include <math/math.h>

#include "game_sdk/entitys/c_base_player.h"

#include <features/legitbot/legitbot.h>
#include <features/prediction_system/prediction_system.h>
#include <features/menu/menu.h>

#include <globals.h>

void bhop(CUserCmd* cmd)
{
    //if (!settings::Misc->bhop_enable)
    //    return;

    CBasePlayer* local_player = get_local_player();
    static bool last_jumped = false, should_fake = false;

    if (!last_jumped && should_fake)
    {
        should_fake = false;
        cmd->buttons |= IN_JUMP;
    }
    else if (cmd->buttons & IN_JUMP)
    {
        if (local_player->get_flags() & FL_ONGROUND)
        {
            last_jumped = true;
            should_fake = true;
        }
        else
        {
            cmd->buttons &= ~IN_JUMP;
            last_jumped = false;
        }
    }
    else
    {
        last_jumped = false;
        should_fake = false;
    }
}

void auto_strafe(CUserCmd* cmd)
{
    //if (!settings::Misc->auto_strafe_enable)
    //    return;

    CBasePlayer* local_player = get_local_player();

    if (!local_player || !local_player->is_alive())
        return;

    if (!(cmd->buttons & IN_JUMP) || !(local_player->get_flags() & FL_ONGROUND))
        return;

    Vector view_angles;
    interfaces->engine->get_viewangles(view_angles);

    static bool side_switch = false;
    side_switch = !side_switch;

    cmd->forwardmove = 0.f;
    cmd->sidemove = side_switch ? 450.f : -450.f;

    float velocity_yaw = local_player->get_velocity().y;

    float rotation = math::fclamp< float >(math::rad2deg(std::atan2(15.f, local_player->get_velocity().length2d())), 0.f, 90.f);

    float abs_yaw = std::fabs(normalize_angel(velocity_yaw - view_angles.y));

    float ideal_yaw_rotation = (side_switch ? rotation : -rotation) + (abs_yaw < 5.f ? velocity_yaw : view_angles.y);

    float cos_rot = std::cos(math::deg2rad(view_angles.y - ideal_yaw_rotation));
    float sin_rot = std::sin(math::deg2rad(view_angles.y - ideal_yaw_rotation));

    cmd->forwardmove = (cos_rot * cmd->forwardmove) - (sin_rot * cmd->sidemove);
    cmd->sidemove = (sin_rot * cmd->forwardmove) + (cos_rot * cmd->sidemove);
}

auto stop_move(CUserCmd* cmd)
{
    auto local_player = get_local_player();

    if (!local_player || !local_player->is_alive())
        return;

    if (local_player->move_type() != MOVETYPE_WALK)
        return;

    Vector vel = local_player->get_velocity();
    vel.z = 0;
    float speed = vel.length2d();

    cmd->forwardmove = 0.f;
    cmd->sidemove = 0.f;
}

bool __stdcall hooks::create_move_hook::hook(float frame_time, CUserCmd* ucmd)
{
	if (!ucmd || !ucmd->command_number)
		return original(interfaces->client_mode, frame_time, ucmd);

	DWORD move;
	_asm mov move, ebp;
	bool& sendpacket = *(***(bool****)(move)-1);

    uintptr_t* frame_ptr;
    __asm mov frame_ptr, ebp;
	
	auto local_player = get_local_player();

	if (!local_player)
		return false;

    static auto should_recharge = false;    //for dt
    if (should_recharge)
    {
        ++globals::ticks::ticks_allowed;

        ucmd->tick_count = INT_MAX;
        ucmd->forwardmove = 0.0f;
        ucmd->sidemove = 0.0f;
        ucmd->upmove = 0.0f;
        ucmd->buttons &= ~IN_ATTACK;
        ucmd->buttons &= ~IN_ATTACK2;

        if (globals::ticks::ticks_allowed >= 16)
        {
            should_recharge = false;
            *(bool*)(*frame_ptr - 0x1C) = true;
        }
        else
            *(bool*)(*frame_ptr - 0x1C) = false;

    	return false;
    }
    if (globals::ticks::ticks_allowed < 16 /*&& dt staff*/)
        should_recharge = true;

    //best tick save imao
    {   
        globals::ticks::backup_tickbase = local_player->get_tick_base();

        if (globals::ticks::next_tickbase_shift)
            globals::ticks::fixed_tickbase = local_player->get_tick_base() - globals::ticks::next_tickbase_shift;
        else
            globals::ticks::fixed_tickbase = globals::ticks::backup_tickbase;
    }

	//best menu fix
    if (menu->open)
    {
        ucmd->buttons &= ~IN_ATTACK;
        ucmd->buttons &= ~IN_ATTACK2;

        stop_move(ucmd);
    }

    globals::ticks::tickbase_shift = 0;
	
	//move
    {
        bhop(ucmd);
        auto_strafe(ucmd);
    }


	
    prediction_system->start(ucmd);
    {
        legit_bot->run(ucmd);

		
    }
    prediction_system->end();

    ucmd->viewangles.clamp();

    interfaces->engine->set_viewangles(ucmd->viewangles);

    if (ucmd->buttons & IN_ATTACK)
        stop_move(ucmd);
	
	return false;
}
