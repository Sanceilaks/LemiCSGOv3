#pragma once


class CGlobalVars
{
public:
	float realtime;
	int framecount;
	float abs_frame_time;
	float abs_frame_start_time_std_dev;
	float curtime;
	float frametime;
	int max_clients;
	int tickcount;
	float interval_per_tick;
	float interpolation_amount;
	int sim_ticks_this_frame;
	int network_protocol;
	void* save_data;

private:
	bool client;

public:
	bool remote_client;

private:
	int timestamp_networking_base;
	int timestamp_randomize_window;
};