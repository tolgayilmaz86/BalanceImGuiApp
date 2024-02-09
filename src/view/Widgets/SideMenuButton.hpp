#pragma once
#include <SFML/Audio.hpp>
#include "styles/IconsFontAwesome5.h"
namespace View::Widget
{

class SideMenuButton
{
public:
    SideMenuButton(const char *label, ImVec2 size = ImVec2(80.0f, 60.0f))
    : label(label), size(size)
  {
    float baseFontSize = 64.0f;
    float iconFontSize = 24.0f;

    // merge in icons from Font Awesome
    static const ImWchar icons_ranges[] = {ICON_MIN_FA, ICON_MAX_16_FA, 0};
    ImFontConfig icons_config;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.GlyphMinAdvanceX = iconFontSize;
    customFont =
      ImGui::GetIO().Fonts->AddFontFromFileTTF(FONT_ICON_FILE_NAME_FAS,
                   iconFontSize,
                   &icons_config,
                   icons_ranges);

    label = ICON_FA_RUNNING;
  }

  bool render()
  {
    // Calculate the position to center the button
    ImVec2 nextPos = ImGui::GetCursorPos();
    ImVec2 windowSize = ImGui::GetWindowSize();
    ImVec2 buttonPos = ImVec2((windowSize.x - size.x) * 0.5f, nextPos.y + size.y * 0.5f);

    // Set up the bigger button with curved corners and red font
    ImGui::PushStyleVar(
      ImGuiStyleVar_FrameRounding,
      4.0f); // Adjust the rounding value for curved corners
    ImGui::PushStyleColor(
      ImGuiCol_Button,
      ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // White color for button
    ImGui::PushStyleColor(
      ImGuiCol_ButtonHovered,
      ImVec4(1.f, 0.8f, 0.8f, 1.0f)); // Slightly darker on hover
    ImGui::PushStyleColor(
      ImGuiCol_ButtonActive,
      ImVec4(0.8f, 0.8f, 0.8f, 1.0f)); // Darker when pressed
    ImGui::PushStyleColor(
      ImGuiCol_Text,
      ImVec4(1.0f, 0.0f, 0.0f, 1.0f)); // Red color for font

    ImGui::PushFont(customFont);
    ImGui::SetCursorPos(buttonPos);
    if (ImGui::Button(label, size))
    {
      isClicked = true;
      label = ICON_FA_PAUSE " PAUSE";
    }
    else
    {
      ICON_FA_RUNNING " START";
    }
    ImGui::PopFont();

    // Pop the style variables and colors
    ImGui::PopStyleVar();
    ImGui::PopStyleColor(4);
    return isClicked;
  }

private:
  bool isClicked = false;
  ImVec2 size;
  const char *label;
  ImFont *customFont;
};

} // namespace View::Widget
