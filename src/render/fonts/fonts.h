#pragma once
#include <imgui/imgui.h>

class Fonts
{
public:
	ImFont* segoe_ui = nullptr;
	
	void init();
	
}; extern Fonts* fonts;