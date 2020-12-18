#pragma once


namespace settings
{
	namespace esp
	{
		static const const char* box_types[] = {
			"Flat",
			"Bounding",
			"Corners",
			//"Angular"
		};
		
		enum ebox_type
		{
			flat,
			bounding,
			corners,
			//angular
		};
		
		extern bool enabled;
		extern bool team_check;
		extern int box_type;
		extern bool only_visible;
		extern bool draw_bone_ids;
		
		extern bool draw_name;
		extern bool draw_health;
		extern bool draw_scoped;
		
		extern float visible_color[4];
		extern float invisible_color[4];
		extern float void_health_color[4];
		extern float health_color[4];
	};

	namespace visuals
	{
		extern int fov;
		extern bool draw_fov;
		
	}

	namespace legit_bot
	{
		extern bool enable;
		extern float fov;
		extern bool only_visible;
		extern bool auto_fire;
		extern int aim_key;
		extern int auto_fire_key;
	}
}
