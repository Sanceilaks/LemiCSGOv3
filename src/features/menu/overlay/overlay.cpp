#include "overlay.h"
#include <render/render.h>

#include <settings/settings.h>

#include "math/math.h"

Overlay* overlay = new Overlay();

void Overlay::draw()
{
	//render->draw_list->AddRectFilled(ImVec2(0, 0), ImVec2(1920, 32), ImGui::GetColorU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)));

	//render->draw_list->AddText(ImVec2(1920 / 2 - 100, 32 / 2 - 10), ImGui::GetColorU32(ImVec4(1.0f, 0.0, 0.0, 1.0)), "Vasa netu");
}
