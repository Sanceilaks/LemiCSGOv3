#include "settings.h"

namespace settings
{
	namespace esp
	{
		bool enabled = true;
		bool team_check = true;
		bool only_visible = false;
		int box_type = ebox_type::flat;
		
		float visible_color[4] = {0, 0, 0, 1};
		float invisible_color[4] = {0, 0, 0, 1};
	}
}
