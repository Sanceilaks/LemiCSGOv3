#pragma once
#include "c_base_entity.h"


enum EEntityFlag
{
	FL_ONGROUND = (1 << 0),
	FL_DUCKING = (1 << 1),
	FL_WATERJUMP = (1 << 2),
	FL_ONTRAIN = (1 << 3),
	FL_INRAIN = (1 << 4),
	FL_FROZEN = (1 << 5),
	FL_ATCONTROLS = (1 << 6),
	FL_CLIENT = (1 << 7),
	FL_FAKECLIENT = (1 << 8),
	MAX_ENTITYFLAGS
};


class CBasePlayer : public CBaseEntity
{
public:
	NETVAR("DT_BaseEntity", "m_iHealth", get_health, int);
	NETVAR("DT_CSPlayer", "m_fFlags", get_flags, int);
	NETVAR("DT_BasePlayer", "m_lifeState", get_life_state, bool);
	NETVAR("DT_CSPlayer", "m_bIsScoped", is_scoped, bool);
	NETVAR("CBasePlayer", "m_vecVelocity[0]", get_velocity, Vector);
	
	inline bool is_alive() { return this->get_life_state() == 0; }
};


inline static CBasePlayer* get_local_player()
{
	return static_cast<CBasePlayer*>(interfaces->entity_list->get_entity_by_index(interfaces->engine->get_local_player()));
}