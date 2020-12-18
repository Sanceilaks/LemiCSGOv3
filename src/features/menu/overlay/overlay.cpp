#include "overlay.h"
#include <render/render.h>
#include <interfaces.h>

#include <settings/settings.h>
#include <globals.h>

#include "math/math.h"

Overlay* overlay = new Overlay();

void Overlay::draw()
{
	//render->draw_list->AddRectFilled(ImVec2(0, 0), ImVec2(1920, 32), ImGui::GetColorU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)));

	//render->draw_list->AddText(ImVec2(1920 / 2 - 100, 32 / 2 - 10), ImGui::GetColorU32(ImVec4(1.0f, 0.0, 0.0, 1.0)), "Vasa netu");

	if (settings::visuals::draw_fov && interfaces->engine->is_in_game())
	{
		auto fov = settings::legit_bot::fov;
		auto sw = 1920;
		auto sh = 1080;
		interfaces->engine->get_screen_size(sw, sh);
		fov = fov > 180 ? 180 : fov;
		// const ImVec2& center, float radius, ImU32 col, int num_segments, float thickness
		render->draw_list->AddCircle(ImVec2(sw / 2, sh / 2), tan(math::deg2rad(fov) / 2) / tan(math::deg2rad(globals::view::last_setup.fov) / 2) * sw, Color(0, 0, 0).get_u32(), 124);
	}
}
