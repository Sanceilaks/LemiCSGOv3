#include "overlay.h"
#include <render/render.h>
#include <interfaces.h>

#include <settings/settings.h>
#include <globals.h>

#include "math/math.h"

#include <game_sdk/entitys/entitys.h>

Overlay* overlay = new Overlay();

void Overlay::draw()
{
	//render->draw_list->AddRectFilled(ImVec2(0, 0), ImVec2(1920, 32), ImGui::GetColorU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)));

	//render->draw_list->AddText(ImVec2(1920 / 2 - 100, 32 / 2 - 10), ImGui::GetColorU32(ImVec4(1.0f, 0.0, 0.0, 1.0)), "Vasa netu");
	auto local_player = get_local_player();

	
	if (settings::visuals::draw_fov && interfaces->engine->is_in_game() && local_player)
	{
		auto ply_fov = globals::view::last_setup.fov;
		auto fov = settings::legit_bot::fov;
		fov = fov > 180 ? 180 : fov;
		
		auto sw = 1920;
		auto sh = 1080;
		interfaces->engine->get_screen_size(sw, sh);
		
		auto ratio = (float)sw / (float)sh;
		auto screen_fov = atanf((ratio) * (0.75f) * tan(math::deg2rad(ply_fov * 0.5f)));

		auto radius = tanf(math::deg2rad(fov)) / tanf(screen_fov) * (sw * 0.5f);
		
		render->draw_list->AddCircle(ImVec2(sw / 2, sh / 2), radius, Color(0, 0, 0).get_u32(), 124);
	}

	if (interfaces->engine->is_in_game() && local_player && settings::esp::draw_bones)
	{
		for (int i = 1; i <= interfaces->gvars->max_clients; i++)
		{
			auto ply = get_player_by_index(i);

			if (player_valid(ply, false))
			{
				for (int j = 1; j <= 128; j++)
				{
					auto pos = ply->get_entity_bone(j);
					auto screen_pos = Vector();
					if (math::world_to_screen(pos, screen_pos))
					{
						auto impos = ImVec2(screen_pos.x, screen_pos.y);

						auto bone = std::to_string(j);
						
						render->draw_list->AddTextOutlined(impos, Color(255, 255, 255).get_u32(), Color(0, 0, 0).get_u32(), bone.c_str());
					}
				}
			}
		}
	}
}
