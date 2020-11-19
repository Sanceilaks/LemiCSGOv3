#include <Windows.h>

#include "../hooks_manager.h"
#include <interfaces.h>

#include <math/math.h>

#include "game_sdk/entitys/c_base_player.h"

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


bool __stdcall hooks::create_move_hook::hook(float frame_time, CUserCmd* ucmd)
{
	if (!ucmd || !ucmd->command_number)
		return original(interfaces->client_mode, frame_time, ucmd);

	DWORD move;
	_asm mov move, ebp;
	bool& sendpacket = *(***(bool****)(move)-1);

	auto local_player = get_local_player();

	if (!local_player)
		return false;

    bhop(ucmd);
    auto_strafe(ucmd);

	
	return false;
}
