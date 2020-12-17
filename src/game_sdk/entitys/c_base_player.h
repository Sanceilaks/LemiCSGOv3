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

enum Bones
{
	PLEVIS = 0,
	SPINE_0,
	SPINE_1,
	SPINE_2,
	SPINE_3,
	NECK_0,
	HEAD_0,
	CALVICLE_L,
	ARM_UPPER_L,
	ARM_LOWER_L,
	HAND_L
};


class CBasePlayer : public CBaseEntity
{
public:
	NETVAR("DT_BasePlayer", "m_iHealth", get_health, int);
	NETVAR("DT_BasePlayer", "m_fFlags", get_flags, int);
	NETVAR("DT_BasePlayer", "m_lifeState", get_life_state, bool);
	NETVAR("DT_CSPlayer", "m_bIsScoped", is_scoped, bool);
	NETVAR("CBasePlayer", "m_vecVelocity[0]", get_velocity, Vector);
	NETVAR("DT_BaseEntity", "m_vecOrigin", get_origin, Vector);
	NETVAR("DT_BasePlayer", "m_vecViewOffset[0]", get_view_offset, Vector);
	NETVAR("DT_BasePlayer", "m_nTickBase", get_tick_base, float);
	
	inline Vector get_eye_pos()
	{
		return this->get_origin() + this->get_view_offset();
	}
	
	inline bool is_alive() { return this->get_life_state() == 0; }

	bool is_sees(CBasePlayer* hit)
	{
		if (!is_alive())
			return false;
		
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
		if (!is_alive())
			return false;
		
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

	bool is_sees_foreach_bone(CBasePlayer* ply, int max_bones = 19)
	{
		if (!is_alive())
			return false;
		
		for (auto i = 0; i <= max_bones; i++)
		{
			auto pos = ply->get_entity_bone(i);
			if (this->is_sees(ply, pos))
			{
				return true;
			}
		}
		return false;
	}
	
	const Vector& get_entity_bone(int bone)
	{
		if (!is_alive())
			return Vector(0.f, 0.f, 0.f);
		
		matrix3x4_t boneMatrix[128];

		if (!this->setup_bones(boneMatrix, 128, 0x00000100, interfaces->engine->get_last_time_stamp()))
			return Vector(0, 0, 0);

		matrix3x4_t hitbox = boneMatrix[bone];

		return Vector(hitbox[0][3], hitbox[1][3], hitbox[2][3]);
	}

	player_info_t get_player_info()
	{
		player_info_t player_info;
		interfaces->engine->get_player_info(index(), &player_info);
		return player_info;
	}

	void get_player_info(player_info_t& info)
	{
		info = get_player_info();
	}

	std::string get_player_name()
	{
		std::string name = get_player_info().m_player_name;
		return name;
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

inline static bool player_valid(CBasePlayer* entity, bool team_check = true, bool visible_check = false)
{
	auto local_player = get_local_player();

	if (!entity || !local_player)
		return false;

	if (!entity->is_player() || entity->is_dormant())
		return false;

	CBasePlayer* ply = entity;

	if (entity == local_player || !ply->is_alive())
		return false;

	if (team_check)
		if (entity->team_num() == local_player->team_num())
			return false;

	if (visible_check)
	{
		if (!local_player->is_sees_foreach_bone(ply))
			return false;
	}


	return true;
}