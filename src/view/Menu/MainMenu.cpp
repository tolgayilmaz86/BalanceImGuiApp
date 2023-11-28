#include "MainMenu.h"
#include "view/Widgets/RedRoundedButton.hpp"
#include "view/Overlay/TimerOverlay.hpp"
//#include <GLFW/glfw3.h>

namespace VM = View::Menu;

 VM::MainMenu::MainMenu(std::unique_ptr<WS::IWindow> windowSystem)
  : AbstractMenu(std::move(windowSystem))
{
}

void VM::MainMenu::render()
{
  constexpr static auto window_flags =
    ImGuiWindowFlags_NoResize |
    ImGuiWindowFlags_NoCollapse |
    ImGuiWindowFlags_NoTitleBar |
    ImGuiWindowFlags_NoScrollbar |
    ImGuiWindowFlags_NoDocking;

  constexpr ImVec4 backgroundColor =
    ImVec4(186.0F / 255.0F, 73.0F / 255.0F, 73.0F / 255.0F, 1.00f);

  ImGui::PushStyleColor(ImGuiCol_WindowBg, backgroundColor);
  ImGui::PushStyleColor(ImGuiCol_Border, backgroundColor);
  ImGui::PushStyleColor(ImGuiCol_BorderShadow, backgroundColor);

  Widget::RedRoundedButton redButton("START");

  bool isRunning = true;
  bool isDragging = false;
  ImVec2 dragStartPos;

  while (windowSystem->isOpen() && isRunning)
  {
    windowSystem->startFrame();

    ImVec2 windowSize = windowSystem->GetWindowSize();
    ImVec2 windowPos = windowSystem->GetWindowPos();

    // Set your menu window position and size
    ImGui::SetNextWindowSize(windowSize);
    ImGui::SetNextWindowPos(windowPos);

    // Check if the left mouse button is pressed
    if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
    {
      if (!isDragging)
      {
        // Start dragging
        isDragging = true;
        dragStartPos = io.MousePos;
      }
      else
      {
        // Calculate the new position based on mouse movement
        ImVec2 mouseDelta = ImVec2(io.MouseDelta.x, io.MouseDelta.y);
        ImVec2 newWindowPos =
            ImVec2(windowPos.x + mouseDelta.x, windowPos.y + mouseDelta.y);

        // Update the window position
        windowPos = newWindowPos;
        windowSystem->SetWindowPos(newWindowPos);
      }
    }
    else
    {
        isDragging = false;
    }

    // Use windowPos to set the position of your MainMenu window
    ImGui::SetNextWindowPos(windowPos);

    //ImGui::SetNextWindowSize(
    //  ImVec2(WS::WINDOW_WIDTH, WS::WINDOW_HEIGHT));
    //ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_FirstUseEver);
    ImGui::Begin("##Balance", nullptr, window_flags);

    ImGui::Text(ICON_FA_CHECK " Tomoto");
    //ImGui::Image(ICON_FA_CHECK,
    //       ImVec2(48, 48)); // If using an image icon
    //ImGui::SameLine();
    //ImGui::Text("Tomoto");
    {
      ImGui::PushStyleColor(
        ImGuiCol_Button,
        ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // White color for button
      ImGui::PushStyleColor(
        ImGuiCol_Text,backgroundColor); // Red color for font
      ImGui::PushStyleColor(
        ImGuiCol_ButtonHovered,
        ImVec4(backgroundColor.x * 0.7f,
             backgroundColor.y * 0.7f,
             backgroundColor.z * 0.7f,
             backgroundColor.w)); // Slightly darker on hover

      float space = ImGui::GetContentRegionAvail().x;
      float buttonSize = 36.0f; // Assuming square buttons of 20x20
      float spacing = ImGui::GetStyle().ItemSpacing.x;

      ImGui::SameLine(space - (buttonSize * 3 + spacing * 2));

      // Button 1
      if (ImGui::Button(ICON_FA_FORWARD "##Button1",
                ImVec2(buttonSize, buttonSize)))
      {
        // Button 1 action
      }
      if (ImGui::IsItemHovered())
        ImGui::SetTooltip("Tooltip for Button 1");

      ImGui::SameLine();

      // Button 2
      if (ImGui::Button(ICON_FA_COG "##Button2",
                ImVec2(buttonSize, buttonSize)))
      {
        // Button 2 action
      }
      if (ImGui::IsItemHovered())
        ImGui::SetTooltip("Tooltip for Button 2");

      ImGui::SameLine();

      // Button 3
      if (ImGui::Button(ICON_FA_WINDOW_CLOSE "##Button3",
                ImVec2(buttonSize, buttonSize)))
      {
        isRunning = false;
      }
      if (ImGui::IsItemHovered())
        ImGui::SetTooltip("Exit");

      ImGui::PopStyleColor(3);
    }// menu buttons

    ImGui::Separator();
    ImGui::Separator();

    if (redButton.render())
    {
    }
    redButton.onButtonPressed();

    ImGui::End();

    ImGui::Render();

    windowSystem->endFrame();
  }

  ImGui::PopStyleColor(3);
}

