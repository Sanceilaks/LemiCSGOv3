#include "../hooks_manager.h"

#include <interfaces.h>

#include <imgui/imgui.h>
#include <imgui/impl/imgui_impl_win32.h>
#include <imgui/impl/imgui_impl_dx9.h>

#include <features/menu/menu.h>
#include <render/render.h>
#include <features/menu/styles/std_style.h>
#include <features/menu/overlay/overlay.h>
#include <features/esp/esp.h>

#include <hack_core.h>

#include <tools/hotkeys_tool.h>

static bool inited = false;
static WNDPROC wnd_proc = nullptr;

LRESULT STDMETHODCALLTYPE my_wndproc(HWND window, UINT message_type, WPARAM w_param, LPARAM l_param)
{
    if (message_type == WM_CLOSE)
    {
        hack_core->destroy();
    }
	
    if (message_type == WM_KEYDOWN)
    {
        if (w_param == VK_INSERT)
            menu->open = !menu->open;
    }
	
    if (ImGui_ImplWin32_WndProcHandler(window, message_type, w_param, l_param) && menu->open)
    {
        interfaces->surface->unlock_cursor();
        return true;
    }
	
    //if (message_type == WM_KEYDOWN)
    //    hotkeys_tool::on_key_down(int(w_param));
    //else if (message_type == WM_KEYUP)
    //    hotkeys_tool::on_key_up(int(w_param));

    //if (message_type == WM_MBUTTONDOWN)
    //    hotkeys_tool::on_key_down(VK_MBUTTON);
    //else if (message_type == WM_MBUTTONUP)
    //    hotkeys_tool::on_key_up(VK_MBUTTON);

    //if (message_type == WM_RBUTTONDOWN)
    //    hotkeys_tool::on_key_down(VK_RBUTTON);
    //else if (message_type == WM_RBUTTONUP)
    //    hotkeys_tool::on_key_up(VK_RBUTTON);

    //if (message_type == WM_LBUTTONDOWN)
    //    hotkeys_tool::on_key_down(VK_LBUTTON);
    //else if (message_type == WM_LBUTTONUP)
    //    hotkeys_tool::on_key_up(VK_LBUTTON);

    //if (message_type == WM_XBUTTONDOWN)
    //    hotkeys_tool::on_key_down(HIWORD(w_param) == XBUTTON1 ? VK_XBUTTON1 : VK_XBUTTON2);
    //else if (message_type == WM_XBUTTONUP)
    //    hotkeys_tool::on_key_up(HIWORD(w_param) == XBUTTON1 ? VK_XBUTTON1 : VK_XBUTTON2);

    //if (message_type == WM_SYSKEYDOWN)
    //    hotkeys_tool::on_key_down(int(w_param));
    //else if (message_type == WM_SYSKEYUP)
    //    hotkeys_tool::on_key_up(int(w_param));

	
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
        set_std_imstyle();
		
        wnd_proc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(game_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(my_wndproc)));

        render->init(device);
		
		inited = true;
	}
}

void render_frame(IDirect3DDevice9* device)
{
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    render->draw_list = ImGui::GetOverlayDrawList();

    menu->draw();

    esp->draw();
	
    overlay->draw();

    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

long hooks::end_scane_hook::hook(IDirect3DDevice9* device)
{
	if (!inited)
		init(device);

    render->device = device;
	
    IDirect3DStateBlock9* pixel_state = NULL;
    IDirect3DVertexDeclaration9* vertex_declaration;
    IDirect3DVertexShader9* vertex_shader;


    device->CreateStateBlock(D3DSBT_PIXELSTATE, &pixel_state);
    device->GetVertexDeclaration(&vertex_declaration);
    device->GetVertexShader(&vertex_shader);

    device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);
	
    render_frame(device);

    pixel_state->Apply();
    pixel_state->Release();
    device->SetVertexDeclaration(vertex_declaration);
    device->SetVertexShader(vertex_shader);
	
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
