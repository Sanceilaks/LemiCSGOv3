#include "../hooks_manager.h"
#include <interfaces.h>
#include <game_sdk/entitys/entitys.h>

void render_player()
{
	IMaterial* material = interfaces->material_system->find_material("debug/debugambientcube", TEXTURE_GROUP_OTHER);

	material->color_modulate(1.f, 1.f, 1.f);
	material->alpha_modulate(1.f);
	material->set_material_var_flag(MATERIAL_VAR_IGNOREZ, true);

	interfaces->model_render->forced_material_override(material);
}

void __stdcall hooks::draw_model_execute::hook(IMatRenderContext* context, const DrawModelState_t& state, const ModelRenderInfo_t& info, matrix3x4_t* bone)
{
	if (interfaces->model_render->is_forced_material_override() && !strstr(info.pModel->szName, "arms") && !strstr(info.pModel->szName, "weapons/v_"))
		return original(interfaces->model_render, context, &state, &info, bone);

	CBasePlayer* ply = get_player_by_index(info.entity_index);
	auto local_player = get_local_player();

	if (ply && local_player)
	{
		if (ply->is_player() && ply->is_alive())
		{
			if (ply->team_num() != local_player->team_num())
			{
				render_player();
			}
		}
	}
	
	original(interfaces->model_render, context, &state, &info, bone);

	interfaces->model_render->forced_material_override(nullptr);
}