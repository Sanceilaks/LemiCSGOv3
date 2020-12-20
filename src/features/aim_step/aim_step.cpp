#include "aim_step.h"
#include <settings/settings.h>

AimStep* aim_step = new AimStep();

bool AimStep::run(Vector src, Vector dst, Vector& out)
{
	float amount = settings::legit_bot::aim_step_amount;
	
	math::normalize_angles(dst);
	Vector delta = dst - src;
	math::normalize_angles(delta);
	bool y_finish = false;
	bool x_finish = false;


	
	if (delta.x > amount)
		src.x += amount;
	else if (delta.x < -amount)
		src.x -= amount;
	else
	{
		x_finish = true;
		src.x = dst.x;
	}

	math::normalize_angles(src);

	if (delta.y > amount)
		src.y += amount;
	else if (delta.y < -amount)
		src.y -= amount;
	else
	{
		y_finish = true;
		src.y = dst.y;
	}

	math::normalize_angles(src);

	out = src;

	return x_finish && y_finish;
}
