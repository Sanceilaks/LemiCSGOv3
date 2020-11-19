#include "widgets.h"



IMGUI_API bool ImGui::RoundedButtonEx(const char* label, const ImVec2& size_arg, float rounding, ImGuiButtonFlags flags)
{
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = CalcTextSize(label, NULL, true);

    ImVec2 pos = window->DC.CursorPos;
    if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
        pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
    ImVec2 size = CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

    const ImRect bb(pos, pos + size);
    ItemSize(size, style.FramePadding.y);
    if (!ItemAdd(bb, id))
        return false;

    if (window->DC.ItemFlags & ImGuiItemFlags_ButtonRepeat)
        flags |= ImGuiButtonFlags_Repeat;
    bool hovered, held;
    bool pressed = ButtonBehavior(bb, id, &hovered, &held, flags);

    // Render
    const ImU32 col = GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
    RenderNavHighlight(bb, id);
    //RenderFrame(bb.Min, bb.Max, col, true, style.FrameRounding);
    RenderFrame(bb.Min, bb.Max, col, true, 6.0f);
    RenderTextClipped(bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &label_size, style.ButtonTextAlign, &bb);

    // Automatically close popups
    //if (pressed && !(flags & ImGuiButtonFlags_DontClosePopups) && (window->Flags & ImGuiWindowFlags_Popup))
    //    CloseCurrentPopup();

    IMGUI_TEST_ENGINE_ITEM_INFO(id, label, window->DC.LastItemStatusFlags);
    return pressed;
}

IMGUI_API bool ImGui::RoundedButton(const char* label, float rounding, const ImVec2& size_arg)
{
    return RoundedButtonEx(label, size_arg, rounding, ImGuiButtonFlags_None);
}

void ImGui::ToggleButton(const char* str_id, bool* v, const ImVec2& size)
{
    ImVec2 p = GetCursorScreenPos();
    ImDrawList* draw_list = GetWindowDrawList();
    ImGuiStyle* style = &ImGui::GetStyle();
	
    float height = GetFrameHeight() + size.y + (GetWindowHeight() * 0.01f);
    float width = height * 1.55f + size.x + (GetWindowWidth() * 0.01f);
    float radius = height * 0.5f;

    InvisibleButton(str_id, ImVec2(width, height));
    if (ImGui::IsItemClicked())
        *v = !*v;

    float t = *v ? 1.0f : 0.0f;

    ImGuiContext& g = *GImGui;

    if (g.LastActiveId == g.CurrentWindow->GetID(str_id))// && g.LastActiveIdTimer < ANIM_SPEED)
    {
        float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
        t = *v ? (t_anim) : (1.0f - t_anim);
    }

	
    //ImU32 col_bg = GetColorU32(style->Colors[ImGuiCol_ChildBg]);
    //
    ImU32 col_bg = GetColorU32(ImVec4(0.109f, 0.156f, 0.192f, 1.0f));
    //if (ImGui::IsItemHovered())
    //{
    //    auto color = style->Colors[ImGuiCol_ButtonHovered];
    //    color.w = t;
    //    col_bg = GetColorU32(color);
    //}
    //else
    //{
    //    auto color = style->Colors[ImGuiCol_Button];
    //    color.w = t;
    //    col_bg = GetColorU32(color);
    //}

    ImU32 slider_color;
    if (*v)
        slider_color = GetColorU32(ImVec4(0.1f, 1.0f, 0.1f, 1.0f));
	else
        slider_color = GetColorU32(ImVec4(1.0f, 0.1f, 0.1f, 1.0f));
	
    draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
    draw_list->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius), radius - 1.5f, slider_color);
}
