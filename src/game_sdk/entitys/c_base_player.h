#pragma once
#include "c_base_entity.h"
#include "game_sdk/interfaces/i_engine_trace.h"


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
	NETVAR("DT_BaseEntity", "m_vecOrigin", get_origin, Vector);
	NETVAR("DT_BasePlayer", "m_vecViewOffset[0]", get_view_offset, Vector);

	inline Vector get_eye_pos()
	{
		return this->get_origin() + this->get_view_offset();
	}
	
	inline bool is_alive() { return this->get_life_state() == 0; }

	bool is_sees(CBasePlayer* hit)
	{
		Ray_t ray;
		trace_t tr;
		CTraceFilter filter;
		filter.pSkip = this;

		Vector eye_pos = this->get_eye_pos();
		Vector end_pos = hit->get_eye_pos();

		ray.init(eye_pos, end_pos);

		interfaces->engine_trace->trace_ray(ray, MASK_SHOT | CONTENTS_GRATE, &filter, &tr);


		if (tr.hit_entity == hit || tr.fraction >= 0.98f)
			return true;
		return false;
	}

	bool is_sees(CBasePlayer* hit, Vector pos)
	{
		Ray_t ray;
		trace_t tr;
		CTraceFilter filter;
		filter.pSkip = this;

		Vector eye_pos = this->get_eye_pos();
		Vector end_pos = pos;

		ray.init(eye_pos, end_pos);

		interfaces->engine_trace->trace_ray(ray, MASK_SHOT | CONTENTS_GRATE, &filter, &tr);


		if (tr.hit_entity == hit || tr.fraction >= 0.98f)
			return true;
		return false;
	}
};


inline static CBasePlayer* get_local_player()
{
	return static_cast<CBasePlayer*>(interfaces->entity_list->get_entity_by_index(interfaces->engine->get_local_player()));
}

inline static CBasePlayer* get_player_by_index(int index)
{
	return static_cast<CBasePlayer*>(interfaces->entity_list->get_entity_by_index(index));
}

inline static CBasePlayer* get_player_by_handle(uintptr_t handle)
{
	return static_cast<CBasePlayer*>(interfaces->entity_list->get_entity_by_handle(handle));
}