#pragma once
#include <SFML/Audio.hpp>
#include "styles/IconsFontAwesome5.h"
namespace View::Widget
{

class RedRoundedButton
{
public:
  RedRoundedButton(const char *label, ImVec2 size = ImVec2(200.0f, 70.0f))
    : label(label), size(size)
  {
    float baseFontSize =
      48.0f; // 13.0f is the size of the default font. Change to the font size you use.
    float iconFontSize =
      baseFontSize * 2.0f /
      4.0f; // FontAwesome fonts need to have their sizes reduced by 2.0f/3.0f in order to align correctly

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

    if (buffer.loadFromFile("start.wav"))
    {
      sound.setBuffer(buffer);
    }
    label = ICON_FA_RUNNING " START";
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
      sound.play();
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

  bool onButtonPressed()
  {
    if (!isClicked)
      return false;

    ImGui::OpenPopup("##Clicked");

    // Check if the popup is open
    if (ImGui::BeginPopupModal("##Clicked",
                   NULL,
                   ImGuiWindowFlags_AlwaysAutoResize |
                   ImGuiWindowFlags_NoDecoration))
    {
      // Render content for the new window
      ImGui::Text("You clicked the button!");
      if (ImGui::Button("Close"))
      {
        ImGui::CloseCurrentPopup();
        isClicked = false;
      }
      ImGui::EndPopup();
    }
    return isClicked;
  }

private:
  bool isClicked = false;
  ImVec2 size;
  sf::Sound sound;
  sf::SoundBuffer buffer;
  const char *label;
  ImFont *customFont;
};

} // namespace View::Widget
