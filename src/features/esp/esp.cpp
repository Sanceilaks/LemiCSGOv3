#include "esp.h"
#include <render/render.h>

#include <game_sdk/entitys/entitys.h>

#include "math/math.h"

#include <game_sdk/misc/color.h>

#include <settings/settings.h>

Esp* esp = new Esp();


bool is_entity_valid(CBaseEntity* entity)
{
	auto local_player = get_local_player();
	
	if (!entity)
		return false;
	
	if (!entity->is_player() || entity->is_dormant())
		return false;

	CBasePlayer* ply = static_cast<CBasePlayer*>(entity);
	
	if (entity == local_player || !ply->is_alive())
		return false;

	if (settings::esp::team_check)
		if (entity->team_num() == local_player->team_num())
			return false;

	if (settings::esp::only_visible)
		if (!local_player->is_sees(ply))
			return false;
	
	return true;
}

bool get_player_box(CBasePlayer* ent, math::box& box_in)	//pasted from unknown source
{
	Vector origin, min, max, flb, brt, blb, frt, frb, brb, blt, flt;
	float left, top, right, bottom;

	origin = ent->get_render_origin();

	min = ent->get_collideable()->obb_mins() + origin;
	max = ent->get_collideable()->obb_maxs() + origin;

	Vector points[] = {
		Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z)
	};
	
	if (!math::world_to_screen(points[3], flb) || !math::world_to_screen(points[5], brt)
		|| !math::world_to_screen(points[0], blb) || !math::world_to_screen(points[4], frt)
		|| !math::world_to_screen(points[2], frb) || !math::world_to_screen(points[1], brb)
		|| !math::world_to_screen(points[6], blt) || !math::world_to_screen(points[7], flt))
		return false;

	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	left = flb.x;
	top = flb.y;
	right = flb.x;
	bottom = flb.y;

	if (left < 0 || top < 0 || right < 0 || bottom < 0)
		return false;

	for (int i = 1; i < 8; i++) {
		if (left > arr[i].x)
			left = arr[i].x;
		if (bottom < arr[i].y)
			bottom = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (top > arr[i].y)
			top = arr[i].y;
	}

	box_in.x = left;
	box_in.y = top;
	box_in.w = right - left;
	box_in.h = bottom - top;

	return true;
}

void draw_box(CBasePlayer* ent, math::box box)
{
	Color col = get_local_player()->is_sees(ent) ? Color(settings::esp::visible_color) : Color(settings::esp::invisible_color);

	if (settings::esp::box_type == settings::esp::flat)
	{
		render->draw_list->AddRect(ImVec2(box.x, box.y), ImVec2(box.x + box.w, box.y + box.h), col.get_u32(), 0, ImDrawCornerFlags_All, 2);
	}
	else if (settings::esp::box_type == settings::esp::bounding)
	{
		render->draw_list->AddRect(ImVec2(box.x - 1.f, box.y - 1.f), ImVec2(box.x + box.w + 1.f, box.y + box.h + 1.f), Color(0, 0, 0).get_u32(), 0, ImDrawCornerFlags_All, 1);

		render->draw_list->AddRect(ImVec2(box.x, box.y), ImVec2(box.x + box.w, box.y + box.h), col.get_u32(), 0, ImDrawCornerFlags_All, 2);
	}
	else if (settings::esp::box_type == settings::esp::corners)
	{
		render->draw_list->AddRect(ImVec2(box.x, box.y), ImVec2(box.x + box.w, box.y + box.h), col.get_u32(), 10.f, ImDrawCornerFlags_All, 2);
	}
}

void Esp::draw()
{
	if (!interfaces->engine->is_in_game())
		return;

	if (!settings::esp::enabled)
		return;
	
	for (auto i = 1; i <= interfaces->engine->get_max_clients(); ++i)
	{
		CBaseEntity* ent = get_entity_by_index(i);

		if (!is_entity_valid(ent))
			continue;

		math::box box;

		if (!get_player_box(static_cast<CBasePlayer*>(ent), box))
			continue;;

		draw_box(static_cast<CBasePlayer*>(ent), box);
	}
}
