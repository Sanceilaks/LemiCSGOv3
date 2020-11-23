#include "fonts.h"
#include <tools/file_tools.h>

Fonts* fonts = new Fonts();

void Fonts::init()
{
	//auto path = file_tools::get_hack_directory_path();
	//path.append("fonts");
	//path.append("Rubik.ttf");

	//if (!file_tools::exist(path.generic_string()))
	//{
	//	
	//}

	ImGuiIO& io = ImGui::GetIO(); //Segoeuib.ttf
	
	segoe_ui = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Segoeuib.ttf", 14, NULL, io.Fonts->GetGlyphRangesCyrillic());
	
}
