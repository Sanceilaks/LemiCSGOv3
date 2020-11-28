#pragma once
#include "../interfaces/i_client_entity.h"
#include <interfaces.h>
#include <tools/netvars.h>

class CBaseEntity : public IClientEntity
{
public:
	NETVAR("DT_BaseEntity", "m_nModelIndex", get_model_index, int32_t);
	NETVAR("DT_BaseEntity", "m_iTeamNum", team_num, int);
	
	bool is_player()
	{
		using original_fn = bool(__thiscall*)(void*);
		return (*(original_fn**)this)[157](this);
	}

	bool is_weapon()
	{
		using original_fn = bool(__thiscall*)(CBaseEntity*);
		return (*(original_fn**)this)[165](this);
	}

	bool is_planted_c4()
	{
		return get_client_class()->class_id == cplantedc4;
	}

	bool is_defuse_kit()
	{
		return get_client_class()->class_id == cbaseanimating;
	}
};

inline static CBaseEntity* get_local_player_entity()
{
	return static_cast<CBaseEntity*>(interfaces->entity_list->get_entity_by_index(interfaces->engine->get_local_player()));
}

inline static CBaseEntity* get_entity_by_index(int index)
{
	return static_cast<CBaseEntity*>(interfaces->entity_list->get_entity_by_index(index));
}

inline static CBaseEntity* get_entity_by_handle(uintptr_t handle)
{
	return static_cast<CBaseEntity*>(interfaces->entity_list->get_entity_by_handle(handle));
}