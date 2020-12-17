#pragma once
#include <game_sdk/misc/c_move_data.h>

class IGameMovement
{
public:
	virtual ~IGameMovement(void) {}

	virtual void process_movement(void* player, CMoveData* move) = 0;
	virtual void reset(void) = 0;
	virtual void start_track_prediction_errors(void* player) = 0;
	virtual void finish_track_prediction_errors(void* player) = 0;
	virtual void diff_print(const char* fmt, ...) = 0;

	virtual Vector const& get_player_mins(bool ducked = false) const = 0;
	virtual Vector const& get_player_maxs(bool ducked = false) const = 0;
	virtual Vector const& get_player_view_offset(bool ducked = false) const = 0;

	virtual bool is_moving_player_stuck(void) const = 0;
	virtual void* get_moving_player(void) const = 0;
	virtual void unblock_pusher(void* player, void* pusher) = 0;

	virtual void setup_movement_bounds(CMoveData* move) = 0;
};