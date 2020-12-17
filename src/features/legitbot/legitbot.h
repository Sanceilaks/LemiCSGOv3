#pragma once
#include <game_sdk/misc/c_user_cmd.h>

#include "game_sdk/entitys/entitys.h"


class LegitBot
{
public:
	auto get_target(CUserCmd* cmd) -> CBasePlayer*;
	void run(CUserCmd* cmd);
	
}; extern LegitBot* legit_bot;