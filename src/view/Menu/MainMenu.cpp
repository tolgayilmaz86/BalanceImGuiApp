#include "MainMenu.h"
#include "view/Widgets/RedRoundedButton.hpp"
#include "view/Overlay/TimerOverlay.hpp"
//#include <GLFW/glfw3.h>

namespace VM = View::Menu;

constexpr ImVec4 backgroundColor =
    ImVec4(186.0F / 255.0F, 73.0F / 255.0F, 73.0F / 255.0F, 0.90f);
constexpr ImVec4 backgroundColor2 =
    ImVec4(125.0F / 255.0F, 83.0F / 255.0F, 162.0F / 255.0F, 0.90f);
constexpr ImVec4 backgroundColor3 =
    ImVec4(57.0F / 255.0F, 112.0F / 255.0F, 51.0F / 255.0F, 0.90f);

constexpr static auto window_flags =
    ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
    ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar |
    ImGuiWindowFlags_NoDocking;

 VM::MainMenu::MainMenu(std::unique_ptr<WS::IWindow> windowSystem)
  : AbstractMenu(std::move(windowSystem))
{
}

void VM::MainMenu::render()
{
  ImGui::PushStyleColor(ImGuiCol_WindowBg, backgroundColor);
  ImGui::PushStyleColor(ImGuiCol_Border, backgroundColor);
  ImGui::PushStyleColor(ImGuiCol_BorderShadow, backgroundColor);

  Widget::RedRoundedButton redButton("START");

  bool isRunning = true;
  int activeTab = 0;

  while (windowSystem->isOpen() && isRunning)
  {
    windowSystem->startFrame();

    ImVec2 windowSize = windowSystem->GetWindowSize();
    ImVec2 windowPos = windowSystem->GetWindowPos();

    handleMove(windowPos);

    // Set your menu window position and size
    ImGui::SetNextWindowSize(windowSize);
    ImGui::SetNextWindowPos(windowPos);

    if (activeTab == 1)
    {
        ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = backgroundColor2;
        ImGui::GetStyle().Colors[ImGuiCol_Border] = backgroundColor2;
        ImGui::GetStyle().Colors[ImGuiCol_BorderShadow] = backgroundColor2;
    }
    else if (activeTab == 2)
    {
        ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = backgroundColor3;
        ImGui::GetStyle().Colors[ImGuiCol_Border] = backgroundColor3;
        ImGui::GetStyle().Colors[ImGuiCol_BorderShadow] = backgroundColor3;
    }
    else
    {
        // Revert to the original background color for Tab 1
        ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = backgroundColor;
        ImGui::GetStyle().Colors[ImGuiCol_Border] = backgroundColor;
        ImGui::GetStyle().Colors[ImGuiCol_BorderShadow] = backgroundColor;
    }

    ImGui::Begin("##BalanceApp", nullptr, window_flags);

    drawTopMenu(isRunning);

    drawTabArea(activeTab);

    if (redButton.render())
    {
    }
    redButton.onButtonPressed();

    // End
    { 
      ImGui::End();
      ImGui::Render();
      windowSystem->endFrame();
    }
  }
  ImGui::PopStyleColor(3);
}

void View::Menu::MainMenu::handleMove(ImVec2& currentPos)
{
  static bool isDragging = false;
  ImVec2 dragStartPos;
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
          ImVec2(currentPos.x + mouseDelta.x, currentPos.y + mouseDelta.y);

      // Update the window position
      currentPos = newWindowPos;
      windowSystem->SetWindowPos(newWindowPos);
    }
  }
  else
  {
    isDragging = false;
  }
}

void View::Menu::MainMenu::drawTopMenu(bool& quit)
{
  ImGui::Text(ICON_FA_CHECK " Tomoto");
  ImGui::PushStyleColor(
      ImGuiCol_Button,
      ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // White color for button
  ImGui::PushStyleColor(
      ImGuiCol_Text,
      ImGui::GetStyle().Colors[ImGuiCol_WindowBg]);
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
    ImGui::SetItemTooltip("1");

  ImGui::SameLine();

  // Button 2
  if (ImGui::Button(ICON_FA_COG "##Button2", ImVec2(buttonSize, buttonSize)))
  {
    // Button 2 action
  }
  if (ImGui::IsItemHovered())
    ImGui::SetItemTooltip("2");

  ImGui::SameLine();

  // Button 3
  if (ImGui::Button(ICON_FA_WINDOW_CLOSE "##Button3",
                    ImVec2(buttonSize, buttonSize)))
  {
    quit = false;
  }
  if (ImGui::IsItemHovered())
    ImGui::SetItemTooltip("Exit");

  ImGui::PopStyleColor(3);

  ImGui::SeparatorText("##");
}

void View::Menu::MainMenu::drawTabArea(int &activeTab)
{

  // Save the original style to revert back later
  ImVec4 originalTabColor = ImGui::GetStyle().Colors[ImGuiCol_Tab];
  ImVec4 originalTabHoveredColor =
      ImGui::GetStyle().Colors[ImGuiCol_TabHovered];
  ImVec4 originalTabActiveColor = ImGui::GetStyle().Colors[ImGuiCol_TabActive];

  // Set the tab colors for transparent background
  ImGui::GetStyle().Colors[ImGuiCol_Tab] =
      ImVec4(1.0f, 1.0f, 1.0f, 0.2f); // Transparent
  ImGui::GetStyle().Colors[ImGuiCol_TabHovered] =
      ImVec4(1.0f, 1.0f, 1.0f, 0.0f); // Slightly visible on hover
  ImGui::GetStyle().Colors[ImGuiCol_TabActive] =
      ImVec4(0.0f, 0.0f, 0.0f, 0.3f); // More visible when active

  int numberOfTabs = 3;
  float tabWidth = windowSystem->GetWindowSize().x / numberOfTabs -
                   ImGui::GetStyle().ItemSpacing.x; // Adjust for spacing
  if (ImGui::BeginTabBar("##TabBar"))
  {
    ImGui::SetNextItemWidth(tabWidth);
    if (ImGui::BeginTabItem("Tab 1"))
    {
      activeTab = 0;
      // Content for Tab 1
      ImGui::Text("This is tab 1");
      ImGui::EndTabItem();
    }
    ImGui::SetNextItemWidth(tabWidth);
    if (ImGui::BeginTabItem("Tab 2"))
    {
      activeTab = 1;
      // Content for Tab 2
      ImGui::Text("This is tab 2");
      ImGui::EndTabItem();
    }
    ImGui::SetNextItemWidth(tabWidth);
    if (ImGui::BeginTabItem("Tab 3"))
    {
      activeTab = 2;
      // Content for Tab 3
      ImGui::Text("This is tab 3");
      ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
  }
  ImGui::GetStyle().Colors[ImGuiCol_Tab] = originalTabColor;
  ImGui::GetStyle().Colors[ImGuiCol_TabHovered] = originalTabHoveredColor;
  ImGui::GetStyle().Colors[ImGuiCol_TabActive] = originalTabActiveColor;
}

