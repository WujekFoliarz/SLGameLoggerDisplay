#include "Style.hpp"
#include "rlImGui.h"
#include "imgui.h"

void SLUI::InitStyle()
{
    ImGuiStyle &style = ImGui::GetStyle();
    ImVec4 *colors = style.Colors;
    ImGuiIO &io = ImGui::GetIO();

    io.Fonts->Clear();
    auto font = io.Fonts->AddFontFromFileTTF(RESOURCE_PATH "Fonts/Good-Old-Dos.ttf", 15);
    io.Fonts->Build();
    ImGui::PushFont(font);

    // --- Layout / shape -----------------------------------------------------
    style.WindowRounding = 0.0f;
    style.ChildRounding = 0.0f;
    style.FrameRounding = 0.0f;
    style.PopupRounding = 0.0f;
    style.ScrollbarRounding = 0.0f;
    style.GrabRounding = 0.0f;
    style.TabRounding = 0.0f;

    style.WindowBorderSize = 1.0f;
    style.ChildBorderSize = 1.0f;
    style.PopupBorderSize = 1.0f;
    style.FrameBorderSize = 1.0f;
    style.TabBorderSize = 1.0f;

    style.WindowPadding = ImVec2(8, 8);
    style.FramePadding = ImVec2(6, 3);
    style.ItemSpacing = ImVec2(6, 4);
    style.ItemInnerSpacing = ImVec2(4, 3);
    style.IndentSpacing = 16.0f;
    style.ScrollbarSize = 12.0f;
    style.GrabMinSize = 8.0f;

    style.WindowTitleAlign = ImVec2(0.0f, 0.5f);

    // --- Palette -------------------------------------------------------------
    // Classic DOS terminal palette: black screen, blue panels, cyan highlights.
    const ImVec4 bgDark = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    const ImVec4 bgPanel = ImVec4(0.00f, 0.00f, 0.45f, 1.00f);
    const ImVec4 bgFrame = ImVec4(0.00f, 0.00f, 0.30f, 1.00f);
    const ImVec4 bgFrameHover = ImVec4(0.00f, 0.35f, 0.45f, 1.00f);
    const ImVec4 bgFrameActive = ImVec4(0.00f, 0.55f, 0.60f, 1.00f);

    const ImVec4 cyan = ImVec4(0.33f, 1.00f, 1.00f, 1.00f);
    const ImVec4 cyanDim = ImVec4(0.00f, 0.65f, 0.75f, 1.00f);
    const ImVec4 white = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    const ImVec4 gray = ImVec4(0.67f, 0.67f, 0.67f, 1.00f);
    const ImVec4 border = gray;

    colors[ImGuiCol_Text] = gray;
    colors[ImGuiCol_TextDisabled] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
    colors[ImGuiCol_WindowBg] = bgDark;
    colors[ImGuiCol_ChildBg] = ImVec4(0, 0, 0, 0);
    colors[ImGuiCol_PopupBg] = bgPanel;
    colors[ImGuiCol_Border] = border;
    colors[ImGuiCol_BorderShadow] = ImVec4(0, 0, 0, 0);

    colors[ImGuiCol_FrameBg] = bgFrame;
    colors[ImGuiCol_FrameBgHovered] = bgFrameHover;
    colors[ImGuiCol_FrameBgActive] = bgFrameActive;

    colors[ImGuiCol_TitleBg] = bgDark;
    colors[ImGuiCol_TitleBgActive] = bgPanel;
    colors[ImGuiCol_TitleBgCollapsed] = bgDark;

    colors[ImGuiCol_MenuBarBg] = bgPanel;

    colors[ImGuiCol_ScrollbarBg] = bgDark;
    colors[ImGuiCol_ScrollbarGrab] = cyanDim;
    colors[ImGuiCol_ScrollbarGrabHovered] = cyan;
    colors[ImGuiCol_ScrollbarGrabActive] = white;

    colors[ImGuiCol_CheckMark] = cyan;

    colors[ImGuiCol_SliderGrab] = cyanDim;
    colors[ImGuiCol_SliderGrabActive] = cyan;

    colors[ImGuiCol_Button] = bgFrame;
    colors[ImGuiCol_ButtonHovered] = bgFrameHover;
    colors[ImGuiCol_ButtonActive] = bgFrameActive;

    colors[ImGuiCol_Header] = bgFrame;
    colors[ImGuiCol_HeaderHovered] = bgFrameHover;
    colors[ImGuiCol_HeaderActive] = bgFrameActive;

    colors[ImGuiCol_Separator] = border;
    colors[ImGuiCol_SeparatorHovered] = cyanDim;
    colors[ImGuiCol_SeparatorActive] = cyan;

    colors[ImGuiCol_ResizeGrip] = cyanDim;
    colors[ImGuiCol_ResizeGripHovered] = cyan;
    colors[ImGuiCol_ResizeGripActive] = white;

    colors[ImGuiCol_Tab] = bgFrame;
    colors[ImGuiCol_TabHovered] = bgFrameHover;
    colors[ImGuiCol_TabActive] = bgPanel;
    colors[ImGuiCol_TabUnfocused] = bgFrame;
    colors[ImGuiCol_TabUnfocusedActive] = bgPanel;

    colors[ImGuiCol_PlotLines] = gray;
    colors[ImGuiCol_PlotLinesHovered] = cyan;
    colors[ImGuiCol_PlotHistogram] = cyanDim;
    colors[ImGuiCol_PlotHistogramHovered] = cyan;

    colors[ImGuiCol_TableHeaderBg] = bgFrame;
    colors[ImGuiCol_TableBorderStrong] = border;
    colors[ImGuiCol_TableBorderLight] = ImVec4(border.x, border.y, border.z, 0.30f);
    colors[ImGuiCol_TableRowBg] = ImVec4(0, 0, 0, 0);
    colors[ImGuiCol_TableRowBgAlt] = ImVec4(1, 1, 1, 0.08f);

    colors[ImGuiCol_TextSelectedBg] = ImVec4(cyanDim.x, cyanDim.y, cyanDim.z, 0.45f);

    colors[ImGuiCol_DragDropTarget] = cyan;
    colors[ImGuiCol_NavHighlight] = cyan;
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1, 1, 1, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0, 0, 0, 0.60f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0, 0, 0, 0.60f);
}