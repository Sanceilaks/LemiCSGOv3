#pragma once
#include <math/math.h>

class CMoveData
{
public:
	bool first_run_of_functions : 1;
	bool game_code_moved_player : 1;
	bool no_air_control : 1;

	unsigned long player_handle;
	int impulse_command;
	Vector view_angles;
	Vector abs_view_angles;
	int buttons;
	int old_buttons;
	float forward_move;
	float slide_move;
	float up_move;

	float max_speed;
	float client_max_speed;

	Vector velocity;
	Vector old_velocity;
	float unk_float;
	Vector angles;
	Vector old_angles;

	float out_step_height;
	Vector out_wish_vel;
	Vector out_jump_vel;

	Vector constrait_center;
	float constrait_radius;
	float constrait_width;
	float constrait_speed_factor;
	float constrait_past_radius;

	void set_abs_origin(const Vector& vec)
	{
		vec_abs_origin = vec;
	}

	const Vector& get_abs_origin() const
	{
		return vec_abs_origin;
	}

private:
	Vector vec_abs_origin;
};