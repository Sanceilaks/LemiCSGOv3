#include "menu.h"

#include <imgui/imgui.h>

#include "widgets.h"


Menu* menu = new Menu();


void Menu::render()
{
	if (!open)
		return;
	static bool togled = false;

	ImGui::GetStyle().Colors[ImGuiCol_ResizeGrip] = ImGui::GetStyle().Colors[ImGuiCol_WindowBg];
	ImGui::GetStyle().Colors[ImGuiCol_ResizeGripActive] = ImGui::GetStyle().Colors[ImGuiCol_ChildBg];
	ImGui::GetStyle().Colors[ImGuiCol_ResizeGripHovered] = ImGui::GetStyle().Colors[ImGuiCol_WindowBg];
	
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(900, 510));
	
	ImGui::Begin("LemiProject", static_cast<bool*>(0), /*ImGuiWindowFlags_NoResize | */ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar /*| ImGuiWindowFlags_AlwaysAutoResize*/);
	//ImGui::SetWindowSize(ImVec2(1024, 600));
	
	ImGui::RoundedButton("Hello");
	ImGui::ToggleButton("###first", &togled, ImVec2(10, -10));
	
	ImGui::End();

	ImGui::PopStyleVar();
}
