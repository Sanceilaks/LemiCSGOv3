#include "settings.h"
#include <Windows.h>


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
		
		float visible_color[4] = {0.f, 1.f, 0.f, 1.f};
		float invisible_color[4] = {1.f, 0.f, 0.f, 1.f};

		float health_color[4] = {0.f, 1.f, 0.f, 1.f};
		float void_health_color[4] = { 180.f, 180.f, 180.f, 1.f };

		bool draw_bone_ids = false;
	}

	namespace visuals
	{
		int fov = 0;
		bool draw_fov = true;
		bool override_aspect_ratio = false;
		float aspect_ratio = 200;
		
	}

	namespace legit_bot
	{
		bool enable = true;
		float fov = 30.f;
		bool only_visible = true;
		bool auto_fire = false;
		int aim_key = VK_LBUTTON;
		int auto_fire_key = VK_LMENU;
		
	}
	
}

