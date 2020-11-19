#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>


namespace ImGui
{
	static float ANIM_SPEED = 0.08f;
	
	IMGUI_API bool RoundedButtonEx(const char* label, const ImVec2& size_args, float rounding, ImGuiButtonFlags flags);
	IMGUI_API bool RoundedButton(const char* label, float rounding = 2.f, const ImVec2& size = ImVec2(0, 0));

	IMGUI_API void ToggleButton(const char* str_id, bool* v, const ImVec2& size = ImVec2(0, 0));
}
