#include "widgets.h"

static ImVector<ImRect> s_GroupPanelLabelStack;

void render_text(const ImVec2& pos, const char* text, const char* text_end, bool hide_after_hash, Color color, ImFont* font)
{
    auto* draw_list = ImGui::GetWindowDrawList();

    const char* text_display_end;
    if (hide_after_hash)
    {
        text_display_end = ImGui::FindRenderedTextEnd(text, text_end);
    }
    else
    {
        if (!text_end)
            text_end = text + strlen(text); // FIXME-OPT
        text_display_end = text_end;
    }

    if (text != text_display_end)
    {
        draw_list->AddText(font, font->FontSize, pos, color.get_u32(), text, text_display_end);
    }
}

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
    //p += ImVec2(10, 10);
	
    ImDrawList* draw_list = GetWindowDrawList();
    ImGuiStyle* style = &ImGui::GetStyle();
	
    float height = /*GetFrameHeight() + size.y + (GetWindowHeight() * 0.01f)*/ size.y;
    float width = /*height * 1.55f + size.x + (GetWindowWidth() * 0.01f)*/ size.x;
    float radius = height * 0.5f;

    InvisibleButton(str_id, ImVec2(width, height));
    if (ImGui::IsItemClicked())
        *v = !*v;

    float t = *v ? 1.0f : 0.0f;

    ImGuiContext& g = *GImGui;

    if (g.LastActiveId == g.CurrentWindow->GetID(str_id))// && g.LastActiveIdTimer < ANIM_SPEED)
    {
        float t_anim = ImSaturate(g.LastActiveIdTimer / /*ANIM_SPEED*/ 0.2);
        t = *v ? (t_anim) : (1.0f - t_anim);
    }

	
    ImU32 col_bg = GetColorU32(ImVec4(0.109f, 0.156f, 0.192f, 1.0f));

    ImU32 slider_color;
    if (*v)
        slider_color = GetColorU32(ImVec4(0.1f, 1.0f, 0.1f, 1.0f));
	else
        slider_color = GetColorU32(ImVec4(1.0f, 0.1f, 0.1f, 1.0f));

    render_text(ImVec2(p.x + width + 10, p.y), str_id, 0, true, Color(255, 255, 255), ImGui::GetFont());
	
   // draw_list->AddText(, Color(255, 255, 255).get_u32(), );
	
    draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
    draw_list->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius), radius - 1.5f, slider_color);
}



bool ImGui::MenuButton(const char* label, const ImVec2& size, const ImVec2& pos, Color color, Color text_color, ImFont* font)
{
    auto* draw_list = GetWindowDrawList();
    auto& style = GetStyle();
    float clicked = false;
	
    ImVec2 total_pos = GetWindowPos() + pos;

    ImGui::SetCursorPos(pos);
    InvisibleButton(label, size);
	
    if (IsItemClicked())
    {
        clicked = true;
    }
        

    ImRect rect(total_pos, total_pos + size);
	
    const auto text_size = CalcTextSize(label, nullptr, true);

    const ImVec2 center_pos = ImVec2(size.x * 0.5f, size.y * 0.5f);
    ImVec2 text_pos_local = ImVec2(center_pos.x - (text_size.x * 0.5f),
                             center_pos.y - (text_size.y * 0.5f));

    ImVec2 text_pos = total_pos + text_pos_local;

    draw_list->AddRectFilled(total_pos, total_pos + size, color.get_u32());

    render_text(text_pos, label, 0, true, text_color, font);

    return clicked;
}

Color g_bg_color;

void ImGui::BeginGroupPanel(const char* name, const ImVec2& size, Color color, Color text_bg_color)
{

    g_bg_color = color;

    ImGui::GetWindowDrawList()->ChannelsSplit(2);
    ImGui::GetWindowDrawList()->ChannelsSetCurrent(1);

    ImGui::BeginGroup();

    auto cursorPos = ImGui::GetCursorScreenPos();
    auto itemSpacing = ImGui::GetStyle().ItemSpacing;
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));

    auto frameHeight = ImGui::GetFrameHeight();
    ImGui::BeginGroup();

    ImVec2 effectiveSize = size;
    if (size.x < 0.0f)
        effectiveSize.x = ImGui::GetContentRegionAvailWidth();
    else
        effectiveSize.x = size.x;
    ImGui::Dummy(ImVec2(effectiveSize.x, 0.0f));

    ImGui::Dummy(ImVec2(frameHeight * 0.5f, 0.0f));
    ImGui::SameLine(0.0f, 0.0f);
    ImGui::BeginGroup();
    ImGui::Dummy(ImVec2(frameHeight * 0.5f, 0.0f));
    auto text_size = ImGui::CalcTextSize(name);
    ImGui::GetWindowDrawList()->AddRectFilled(cursorPos, ImVec2(cursorPos.x + effectiveSize.x, cursorPos.y + text_size.y), text_bg_color.get_u32());
    ImGui::SetCursorPos(ImVec2((ImGui::GetCursorPos().x + effectiveSize.x * 0.5f) - text_size.x * 0.5f, ImGui::GetCursorPos().y));
    ImGui::Text(name);
    ImGui::SameLine(0.0f, 0.0f);
    ImGui::Dummy(ImVec2(0.0, frameHeight + itemSpacing.y));
    ImGui::BeginGroup();

    ImGui::PopStyleVar(2);

    ImGui::GetCurrentWindow()->ContentRegionRect.Max.x -= frameHeight * 0.5f;
    ImGui::GetCurrentWindow()->Size.x -= frameHeight;

    ImGui::PushItemWidth(effectiveSize.x - frameHeight);
}

void ImGui::EndGroupPanel()
{
    ImGui::PopItemWidth();

    auto itemSpacing = ImGui::GetStyle().ItemSpacing;

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));

    auto frameHeight = ImGui::GetFrameHeight();

    ImGui::EndGroup();

    //ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(0, 255, 0, 64), 4.0f);

    ImGui::EndGroup();

    ImGui::SameLine(0.0f, 0.0f);
    ImGui::Dummy(ImVec2(frameHeight * 0.5f, 0.0f));
    ImGui::Dummy(ImVec2(0.0, frameHeight - frameHeight * 0.5f - itemSpacing.y));

    ImGui::EndGroup();

    auto itemMin = ImGui::GetItemRectMin();
    auto itemMax = ImGui::GetItemRectMax();

    ImGui::PopStyleVar(2);

    ImGui::GetCurrentWindow()->ContentRegionRect.Max.x += frameHeight * 0.5f;
    ImGui::GetCurrentWindow()->Size.x += frameHeight;

    ImGui::Dummy(ImVec2(0.0f, 0.0f));

    ImGui::EndGroup();

    ImGui::GetWindowDrawList()->ChannelsSetCurrent(0);
    ImGui::GetWindowDrawList()->AddRectFilled(itemMin, itemMax, g_bg_color.get_u32());
    ImGui::GetWindowDrawList()->ChannelsMerge();
}

bool ImGui::SizedCombo(const char* label, int* current_item, const char* const items[], int items_count, ImVec2 size,
	int height_in_items)
{
    PushItemWidth(size.x);
    const bool value_changed = Combo(label, current_item, items, items_count, height_in_items);
    PopItemWidth();
    return value_changed;
}
