#pragma once
#include "../interfaces/i_client_entity.h"
#include <interfaces.h>
#include <tools/netvars.h>

class CBaseEntity : public IClientEntity
{
public:
	NETVAR("CBaseEntity", "m_nModelIndex", get_model_index, int32_t);
	NETVAR("CBaseEntity", "m_iTeamNum", team_num, int);
	
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