#pragma once


namespace settings
{
	namespace esp
	{
		static const const char* box_types[] = {
			"Flat",
			"Bounding",
			"Corners"
		};
		
		enum ebox_type
		{
			flat,
			bounding,
			corners
		};
		
		extern bool enabled;
		extern bool team_check;
		extern int box_type;
		extern bool only_visible;
		
		
		extern float visible_color[4];
		extern float invisible_color[4];
	};
}
