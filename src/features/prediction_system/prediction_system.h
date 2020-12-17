#pragma once
#include <interfaces.h>


class PredictionSystem
{
public:
	void start(CUserCmd* ucmd);
	void end();
	
private:
	float old_curtime;
	float old_frametime;
	CMoveData move_data;

	int* prediction_random_seed;
}; extern PredictionSystem* prediction_system;

