#pragma once
#include "c_base_entity.h"
#include "game_sdk/interfaces/i_engine_trace.h"
#include "../misc/e_handle.h"
#include "items.h"

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
	BONE_HEAD = 8,
	BONE_NEAK = 2,
	BONE_UPPER_BODY = 7,
	BONE_BODY = 6,
	BONE_CENTER_BODY = 5,
	BONE_BUTTOM_BODY = 4,
	BONE_PLEVIS = 3,
	BONE_RIGHT_LEG_1 = 72,
	BONE_RIGHT_LEG_2 = 77,
	BONE_RIGHT_LEG_3 = 78,
	BONE_RIGHT_LEG_4 = 73,
	BONE_RIGHT_FOOT_1 = 74,
	BONE_RIGHT_FOOT_2 = 76,
	BONE_RIGHT_FOOT_3 = 75,

	BONE_LEFT_LEG_1 = 65,
	BONE_LEFT_LEG_2 = 70,
	BONE_LEFT_LEG_3 = 66,
	BONE_LEFT_LEG_4 = 71,
	BONE_LEFT_FOOT_1 = 69,
	BONE_LEFT_FOOT_2 = 68,
	BONE_LEFT_FOOT_3 = 67,

	BONE_RIGHT_ARM_1 = 38,
	BONE_RIGHT_ARM_2 = 64,
	BONE_RIGHT_ARM_3 = 39,
	BONE_RIGHT_ARM_4 = 62,

	BONE_RIGHT_HAND = 60,

	BONE_LEFT_ARM_1 = 10,
	BONE_LEFT_ARM_2 = 36,
	BONE_LEFT_ARM_3 = 11,
	BONE_LEFT_ARM_4 = 34,

	BONE_LEFT_HAND = 81
};

enum MoveType : int
{
	MOVETYPE_NONE = 0,
	MOVETYPE_ISOMETRIC,
	MOVETYPE_WALK,
	MOVETYPE_STEP,
	MOVETYPE_FLY,
	MOVETYPE_FLYGRAVITY,
	MOVETYPE_VPHYSICS,
	MOVETYPE_PUSH,
	MOVETYPE_NOCLIP,
	MOVETYPE_LADDER,
	MOVETYPE_OBSERVER,
	MOVETYPE_CUSTOM
};

class CBasePlayer : public CBaseEntity
{
public:	//m_bIsDefusing
	NETVAR("DT_BasePlayer", "m_iHealth", get_health, int);
	NETVAR("DT_BasePlayer", "m_fFlags", get_flags, int);
	NETVAR("DT_BasePlayer", "m_lifeState", get_life_state, bool);
	NETVAR("DT_CSPlayer", "m_bIsScoped", is_scoped, bool);
	NETVAR("CBasePlayer", "m_vecVelocity[0]", get_velocity, Vector);
	NETVAR("DT_BaseEntity", "m_vecOrigin", get_origin, Vector);
	NETVAR("DT_BasePlayer", "m_vecViewOffset[0]", get_view_offset, Vector);
	NETVAR("DT_BasePlayer", "m_nTickBase", get_tick_base, int);
	NETVAR("DT_CSPlayer", "m_bIsDefusing", is_defusing, bool);
	NETVAR("DT_BaseCombatCharacter", "m_flNextAttack", get_next_attack, float);
	NETVAR("DT_BaseCombatCharacter", "m_hActiveWeapon", get_active_weapon_handle, CHandle<CWeapon>);
	NETVAR("DT_BasePlayer", "m_aimPunchAngle", get_aim_punch, Vector);
	NETVAR("DT_BasePlayer", "m_iFOV", get_fov, int32_t);
	NETVAR("DT_BasePlayer", "m_iDefaultFOV", get_def_fov, int32_t);
	
	
	OFFSET(int, move_type, 0x25C);

	auto get_active_weapon() -> CWeapon*
	{
		if (!this)
			return nullptr;

		return (CWeapon*)interfaces->entity_list->get_entity_by_handle(get_active_weapon_handle());
	}
	
	inline Vector get_eye_pos()
	{
		return this->get_origin() + this->get_view_offset();
	}
	
	inline bool is_alive() { return this->get_life_state() == 0; }

	bool is_sees(CBasePlayer* hit)
	{
		if (!this)
			return false;
		
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
		if (!this)
			return false;
		
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

	bool is_sees_foreach_bone(CBasePlayer* ply, int max_bones = 128)
	{
		if (!this)
			return false;
		
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
		if (!this)
			return Vector();
		
		if (!is_alive())
			return Vector(0.f, 0.f, 0.f);
		
		matrix3x4_t boneMatrix[128];

		if (!this->setup_bones(boneMatrix, 128, 0x00000100, interfaces->gvars->curtime))
			return Vector(0, 0, 0);

		matrix3x4_t hitbox = boneMatrix[bone];

		return Vector(hitbox[0][3], hitbox[1][3], hitbox[2][3]);
	}

	player_info_t get_player_info()
	{
		if (!this)
			return player_info_t();
		
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
		if (!this)
			return std::string();
		
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

inline static CBasePlayer* get_player_by_handle(CBaseHandle handle)
{
	return static_cast<CBasePlayer*>(interfaces->entity_list->get_entity_by_handle(handle));
}

inline static bool player_valid(CBasePlayer* entity, bool team_check = true, bool visible_check = false)
{
	auto local_player = get_local_player();

	if (!entity || !local_player)
		return false;

	if (!entity->is_player() || !entity->is_alive() || entity->is_dormant())
		return false;

	if (entity == local_player)
		return false;

	if (team_check)
		if (entity->team_num() == local_player->team_num())
			return false;

	if (visible_check)
	{
		if (!local_player->is_sees_foreach_bone(entity))
			return false;
	}


	return true;
}