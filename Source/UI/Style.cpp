#include "Style.hpp"
#include "rlImGui.h"
#include "imgui.h"

void UI::InitStyle()
{
    ImGuiStyle &style = ImGui::GetStyle();
    ImVec4 *colors = style.Colors;

    // --- Layout / shape -----------------------------------------------------
    style.WindowRounding = 2.0f;
    style.ChildRounding = 2.0f;
    style.FrameRounding = 1.0f;
    style.PopupRounding = 2.0f;
    style.ScrollbarRounding = 2.0f;
    style.GrabRounding = 1.0f;
    style.TabRounding = 1.0f;

    style.WindowBorderSize = 1.0f;
    style.ChildBorderSize = 1.0f;
    style.PopupBorderSize = 1.0f;
    style.FrameBorderSize = 1.0f;
    style.TabBorderSize = 1.0f;

    style.WindowPadding = ImVec2(10, 10);
    style.FramePadding = ImVec2(8, 4);
    style.ItemSpacing = ImVec2(8, 6);
    style.ItemInnerSpacing = ImVec2(6, 4);
    style.IndentSpacing = 18.0f;
    style.ScrollbarSize = 14.0f;
    style.GrabMinSize = 10.0f;

    style.WindowTitleAlign = ImVec2(0.02f, 0.5f);

    // --- Palette -------------------------------------------------------------
    // Base: near-black / charcoal, like the SCP:SL escape-menu and pause overlay
    const ImVec4 bgDark = ImVec4(0.06f, 0.06f, 0.07f, 0.95f);
    const ImVec4 bgPanel = ImVec4(0.09f, 0.09f, 0.10f, 0.95f);
    const ImVec4 bgFrame = ImVec4(0.12f, 0.11f, 0.12f, 1.00f);
    const ImVec4 bgFrameHover = ImVec4(0.20f, 0.10f, 0.10f, 1.00f);
    const ImVec4 bgFrameActive = ImVec4(0.30f, 0.09f, 0.09f, 1.00f);

    // Accent: SCP Foundation red / containment-warning red
    const ImVec4 red = ImVec4(0.72f, 0.11f, 0.11f, 1.00f);
    const ImVec4 redBright = ImVec4(0.85f, 0.16f, 0.14f, 1.00f);
    const ImVec4 redDim = ImVec4(0.45f, 0.08f, 0.08f, 1.00f);

    // Text: off-white / faded grey, like the in-game console and info panels
    const ImVec4 textMain = ImVec4(0.90f, 0.90f, 0.88f, 1.00f);
    const ImVec4 textDim = ImVec4(0.55f, 0.54f, 0.52f, 1.00f);
    const ImVec4 textWarn = ImVec4(0.95f, 0.55f, 0.20f, 1.00f); // warning-orange, used sparingly

    const ImVec4 border = ImVec4(0.25f, 0.06f, 0.06f, 0.60f);

    colors[ImGuiCol_Text] = textMain;
    colors[ImGuiCol_TextDisabled] = textDim;
    colors[ImGuiCol_WindowBg] = bgDark;
    colors[ImGuiCol_ChildBg] = ImVec4(0, 0, 0, 0);
    colors[ImGuiCol_PopupBg] = bgPanel;
    colors[ImGuiCol_Border] = border;
    colors[ImGuiCol_BorderShadow] = ImVec4(0, 0, 0, 0);

    colors[ImGuiCol_FrameBg] = bgFrame;
    colors[ImGuiCol_FrameBgHovered] = bgFrameHover;
    colors[ImGuiCol_FrameBgActive] = bgFrameActive;

    colors[ImGuiCol_TitleBg] = bgDark;
    colors[ImGuiCol_TitleBgActive] = redDim;
    colors[ImGuiCol_TitleBgCollapsed] = bgDark;

    colors[ImGuiCol_MenuBarBg] = bgPanel;

    colors[ImGuiCol_ScrollbarBg] = bgDark;
    colors[ImGuiCol_ScrollbarGrab] = redDim;
    colors[ImGuiCol_ScrollbarGrabHovered] = red;
    colors[ImGuiCol_ScrollbarGrabActive] = redBright;

    colors[ImGuiCol_CheckMark] = redBright;

    colors[ImGuiCol_SliderGrab] = red;
    colors[ImGuiCol_SliderGrabActive] = redBright;

    colors[ImGuiCol_Button] = bgFrame;
    colors[ImGuiCol_ButtonHovered] = redDim;
    colors[ImGuiCol_ButtonActive] = red;

    colors[ImGuiCol_Header] = redDim;
    colors[ImGuiCol_HeaderHovered] = red;
    colors[ImGuiCol_HeaderActive] = redBright;

    colors[ImGuiCol_Separator] = border;
    colors[ImGuiCol_SeparatorHovered] = red;
    colors[ImGuiCol_SeparatorActive] = redBright;

    colors[ImGuiCol_ResizeGrip] = redDim;
    colors[ImGuiCol_ResizeGripHovered] = red;
    colors[ImGuiCol_ResizeGripActive] = redBright;

    colors[ImGuiCol_Tab] = bgFrame;
    colors[ImGuiCol_TabHovered] = red;
    colors[ImGuiCol_TabActive] = redDim;
    colors[ImGuiCol_TabUnfocused] = bgFrame;
    colors[ImGuiCol_TabUnfocusedActive] = bgFrameHover;

    colors[ImGuiCol_PlotLines] = textDim;
    colors[ImGuiCol_PlotLinesHovered] = redBright;
    colors[ImGuiCol_PlotHistogram] = red;
    colors[ImGuiCol_PlotHistogramHovered] = redBright;

    colors[ImGuiCol_TableHeaderBg] = bgFrame;
    colors[ImGuiCol_TableBorderStrong] = border;
    colors[ImGuiCol_TableBorderLight] = ImVec4(border.x, border.y, border.z, 0.30f);
    colors[ImGuiCol_TableRowBg] = ImVec4(0, 0, 0, 0);
    colors[ImGuiCol_TableRowBgAlt] = ImVec4(1, 1, 1, 0.02f);

    colors[ImGuiCol_TextSelectedBg] = ImVec4(redBright.x, redBright.y, redBright.z, 0.35f);

    colors[ImGuiCol_DragDropTarget] = textWarn;
    colors[ImGuiCol_NavHighlight] = redBright;
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1, 1, 1, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0, 0, 0, 0.60f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0, 0, 0, 0.60f);


}