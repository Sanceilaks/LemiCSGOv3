#include "../hooks_manager.h"

#include <interfaces.h>

#include <imgui/imgui.h>
#include <imgui/impl/imgui_impl_win32.h>
#include <imgui/impl/imgui_impl_dx9.h>

#include <features/menu/menu.h>

static bool inited = false;
static WNDPROC wnd_proc = nullptr;

LRESULT STDMETHODCALLTYPE my_wndproc(HWND window, UINT message_type, WPARAM w_param, LPARAM l_param)
{
    if (message_type == WM_KEYDOWN)
    {
        if (w_param == VK_INSERT)
            menu->open = !menu->open;
        //if (w_param == VK_DELETE)
        //    //CHackCore::get().shutdown();
    }

    if (ImGui_ImplWin32_WndProcHandler(window, message_type, w_param, l_param) && menu->open)
    {
        return true;
    }
    return CallWindowProc(wnd_proc, window, message_type, w_param, l_param);
}


void init(IDirect3DDevice9* device)
{
    ImGui::CreateContext();
	
	auto game_hwnd = FindWindow("Valve001", 0);
	if (game_hwnd != NULL)
	{
        ImGui_ImplWin32_Init(game_hwnd);
        ImGui_ImplDX9_Init(device);

        ImGui::GetIO().IniFilename = nullptr;
        ImGui::StyleColorsDark();
		
        wnd_proc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(game_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(my_wndproc)));
		
		inited = true;
	}
}

long hooks::end_scane_hook::hook(IDirect3DDevice9* device)
{
	if (!inited)
		init(device);

    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    menu->render();

    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	
	return original(device);
}


long hooks::reset_hook::hook(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* present_parameters)
{
    auto ret = original(device, present_parameters);

    ImGui_ImplDX9_InvalidateDeviceObjects();

    if (ret > 0)
        ImGui_ImplDX9_CreateDeviceObjects();

    return ret;
}
