#include "menu.h"

#include <imgui/imgui.h>
#include <render/render.h>

#include "widgets.h"

#include <settings/settings.h>

#define COLOR_EDIT_FLAGS ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_NoInputs

Menu* menu = new Menu();


void Menu::draw()
{
	if (!open)
		return;
	
	ImGui::Begin("LemiProject", static_cast<bool*>(0), /*ImGuiWindowFlags_NoResize | */ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar /*| ImGuiWindowFlags_AlwaysAutoResize*/);
	//ImGui::SetWindowSize(ImVec2(1024, 600));
	
	ImGui::RoundedButton("Hello");
	ImGui::ToggleButton("Enabled##esp", &settings::esp::enabled, ImVec2(10, -10));
	ImGui::ColorEdit4("Visible color##esp", settings::esp::visible_color, COLOR_EDIT_FLAGS);

	
	ImGui::End();
}
