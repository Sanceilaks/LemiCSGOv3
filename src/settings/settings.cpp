#include "settings.h"

namespace settings
{
	namespace esp
	{
		bool enabled = true;
		bool team_check = true;
		bool only_visible = false;
		int box_type = ebox_type::flat;
		
		bool draw_name = true;
		bool draw_health = true;
		bool draw_scoped = false;
		
		float visible_color[4] = {0, 0, 0, 1};
		float invisible_color[4] = {0, 0, 0, 1};

		float health_color[4] = {0.f, 1.f, 0.f, 1.f};
		float void_health_color[4] = { 180.f, 180.f, 180.f, 1.f };

		bool draw_bone_ids = false;
	}

	namespace visuals
	{
		int fov = 0;
		
	}
}
