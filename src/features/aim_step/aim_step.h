#pragma once
#include <math/math.h>



class AimStep
{
public:
	bool run(Vector src, Vector dst, Vector& out);
	
}; extern AimStep* aim_step;