#include "menu.h"


#include <string>
#include <imgui/imgui.h>
#include <render/render.h>

#include "widgets.h"

#include <settings/settings.h>

#define COLOR_EDIT_FLAGS ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_DisplayHex
#define COLOR_PICKER_FLAGS 
#define TUBS_NUM 7
#define TAB_SIZE_W 127.f
#define TAB_SIZE_H 50.f
#define CHILDE_SIZE_W 330.f
#define TABS_MARGIN 6.f
#define CHILD_MARGIN 8.f

enum class tabs
{
	legit_bot,
	rage,
	visuals,
	changer,
	color,
	misc,
	settings
};

static const char* tabs_names[] = {
	"LEGITBOT##menubutton",
	"RAGE##menubutton",
	"VISUALS##menubutton",
	"CHANGER##menubutton",
	"COLOR##menubutton",
	"MISC##menubutton",
	"SETTINGS##menubutton"
};

tabs current_tab = tabs::visuals;

Menu* menu = new Menu();

//hide this
void draw_top_bar()
{	
	ImGui::BeginGroup();
	///logo
	ImGui::PushFont(fonts->arial_menu);
	
	auto text_size = ImGui::CalcTextSize("LemiProject", 0, false);
	auto p = ImVec2((text_size.x + text_size.x * 0.3f), text_size.y);

	
	ImGui::SetCursorPos(ImVec2(text_size.x * 0.1f, 10));
	
	ImGui::TextColored(ImVec4(0.3, 1, 0.3, 1), "LemiProject");

	ImGui::PopFont();
	
	for (auto i = 0; i < TUBS_NUM; i++)
	{
		ImVec2 pos = i == 0 ? ImVec2(p.x, 0) : ImVec2(p.x + (i + TAB_SIZE_W * static_cast<float>(i) + TABS_MARGIN * i), 0);
		
		if (ImGui::MenuButton(tabs_names[i], ImVec2(TAB_SIZE_W, TAB_SIZE_H), pos, 
			current_tab == static_cast<tabs>(i) ? Color(42, 42, 42) : Color(32, 32, 32),
			Color(255, 255, 255), fonts->segoe_ui))
		{
			current_tab = static_cast<tabs>(i);
		}
	}
	
	ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y + 49), ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowWidth(), ImGui::GetWindowPos().y + 53), ImGui::GetColorU32(ImVec4(0.12549f, 0.12549f, 0.12549f, 1.0f)));
	ImGui::EndGroup();
}

void draw_legit_bot()
{
	
}

void draw_rage()
{
	
}

void draw_visuals()
{
	ImGui::BeginGroupPanel("ESP", ImVec2(CHILDE_SIZE_W, -1.f), Color(ImGui::GetStyle().Colors[ImGuiCol_ChildBg]), Color(32, 32, 32));
	
	ImGui::ToggleButton("Enable##espbox", &settings::esp::enabled, ImVec2(45, 20));

	ImGui::EndGroupPanel();
}

void draw_changer()
{
	
}

void draw_color()
{
	ImGui::BeginGroupPanel("ESP", ImVec2(CHILDE_SIZE_W, -1.f), Color(ImGui::GetStyle().Colors[ImGuiCol_ChildBg]), Color(32, 32, 32));

	ImGui::ColorEdit4("Visible##espbox", settings::esp::visible_color, COLOR_EDIT_FLAGS);

	ImGui::EndGroupPanel();

	
}

void draw_misc()
{
	
}

void draw_settings()
{
	
}

void Menu::draw()
{
	if (!open)
		return;

	ImGui::ANIM_SPEED = 50.f;
	
	ImGui::PushFont(fonts->segoe_ui);
	
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::Begin("LemiProjectWindow", static_cast<bool*>(0), ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar /*| ImGuiWindowFlags_AlwaysAutoResize*/);
	ImGui::PopStyleVar();
	ImGui::SetWindowSize(ImVec2(1150, 620));

	draw_top_bar();

	switch (current_tab)
	{
	case tabs::legit_bot:
		draw_legit_bot();
		break;
	case tabs::rage:
		draw_rage();
		break;
	case tabs::visuals:
		draw_visuals();
		break;
	case tabs::color:
		draw_color();
		break;
	case tabs::changer:
		draw_changer();
		break;
	case tabs::misc:
		draw_misc();
		break;
	case tabs::settings:
		draw_settings();
		break;
	}
	
	ImGui::End();
	ImGui::PopFont();
}
