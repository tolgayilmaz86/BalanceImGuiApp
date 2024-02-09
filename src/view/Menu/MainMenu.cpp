#include "MainMenu.h"
#include "view/Widgets/RedRoundedButton.hpp"
#include "view/Overlay/TimerOverlay.hpp"
#include "styles/IconsFontAwesome5.h"

namespace VM = View::Menu;

constexpr ImVec4 HexToImVec4(const unsigned int hexValue)
{
    float r =
        ((hexValue >> 24) & 0xFF) / 255.0f; // Extract the RR byte and normalize
    float g =
        ((hexValue >> 16) & 0xFF) / 255.0f; // Extract the GG byte and normalize
    float b =
        ((hexValue >> 8) & 0xFF) / 255.0f; // Extract the BB byte and normalize
    float a = ((hexValue)&0xFF) / 255.0f;  // Extract the AA byte and normalize

    return ImVec4(r, g, b, a);
}

constexpr ImVec4 backgroundColor = HexToImVec4(0x3d3d3dFF);
constexpr ImVec4 backgroundColor2 = HexToImVec4(0x4b4b4bFF);
constexpr ImVec4 backgroundColor3 = HexToImVec4(0x778ca3FF);

const ImVec4* activeBackGroundColor = &backgroundColor;

constexpr static auto window_flags =
    ImGuiWindowFlags_NoResize
  | ImGuiWindowFlags_NoCollapse
  | ImGuiWindowFlags_NoTitleBar
  | ImGuiWindowFlags_NoScrollbar
  | ImGuiWindowFlags_NoDocking;

 VM::MainMenu::MainMenu(std::unique_ptr<WS::IWindow> windowSystem)
  : AbstractMenu(std::move(windowSystem))
{
}

void VM::MainMenu::show()
{
  auto windowSystem = getWindowSystem();

  ImGui::PushStyleColor(ImGuiCol_WindowBg, backgroundColor);
  ImGui::PushStyleColor(ImGuiCol_Border, backgroundColor);
  ImGui::PushStyleColor(ImGuiCol_BorderShadow, backgroundColor);

  Widget::RedRoundedButton redButton("START");

  bool isRunning = true;
  int activeTab = 0;

  View::Overlay::TimerOverlay timer(windowSystem);

  ImVec2 p_min, p_max;

  while (windowSystem->isOpen() && isRunning)
  {
    windowSystem->startFrame();
    ImVec2 windowSize = ImVec2(WS::MENU_WINDOW_WIDTH + 80, WS::MENU_WINDOW_HEIGHT);
    ImVec2 windowPos = windowSystem->GetWindowPos();

    handleMove(windowPos);

    // Set your menu window position and size
    ImGui::SetNextWindowSize(windowSize);
    ImGui::SetNextWindowPos(windowPos);

    ImGui::Begin("##BalanceApp", nullptr, window_flags);

    //SideMenu
    {
      ImGui::BeginChild("##SideMenu", ImVec2(60, WS::MENU_WINDOW_HEIGHT), true);

      ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 64.0f); // round buttons
      std::string tabNames[] = {ICON_FA_CROSSHAIRS,
                                ICON_FA_EYE,
                                ICON_FA_COG,
                                ICON_FA_SAVE};

      for (int i = 0; i < 4; i++)
      {
        std::string it = tabNames[i];
        ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.15, 0.5));
        ImGui::PushStyleColor(
            ImGuiCol_Button,
           *activeBackGroundColor); // White color for button
        ImGui::PushStyleColor(
            ImGuiCol_ButtonHovered,
            ImVec4(1.f, 0.8f, 0.8f, 1.0f)); // Slightly darker on hover
        ImGui::PushStyleColor(
            ImGuiCol_ButtonActive,
            ImVec4(0.8f, 0.8f, 0.8f, 1.0f)); // Darker when pressed
        ImGui::PushStyleColor(ImGuiCol_Text,
                              ImGui::GetStyle().Colors[ImGuiCol_Text]);
        if (ImGui::Button(it.c_str(), ImVec2(80, 120)))
        {
            activeTab = i + 1;
        }
        ImGui::Spacing();
        ImGui::PopStyleVar();
        ImGui::PopStyleColor(4);
      }
      ImGui::PopStyleVar();

      p_min = ImGui::GetWindowPos(); // Top-left
      p_max = ImVec2(p_min.x + ImGui::GetWindowWidth(),
                            p_min.y + ImGui::GetWindowHeight()); // Bottom-right


      ImGui::EndChild();
    }

    ImGui::SameLine();

    // Main Window
    {
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

      ImGui::BeginChild("##MainMenu",
                        ImVec2(WS::MENU_WINDOW_WIDTH, WS::MENU_WINDOW_HEIGHT),
                        true);
      drawTopMenu(isRunning);

      drawTabArea();

      if (redButton.render())
      {
        timer.render();
      }
      ImGui::EndChild();
    }
    ImDrawList *draw_list = ImGui::GetWindowDrawList();
    draw_list->AddRectFilled(p_min,
                             p_max,
                             IM_COL32(255, 255, 255, 80)); // Fully transparent

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

void View::Menu::MainMenu::drawTabArea()
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
      // Content for Tab 1
      ImGui::Text("This is tab 1");
      ImGui::EndTabItem();
    }
    ImGui::SetNextItemWidth(tabWidth);
    if (ImGui::BeginTabItem("Tab 2"))
    {
      // Content for Tab 2
      ImGui::Text("This is tab 2");
      ImGui::EndTabItem();
    }
    ImGui::SetNextItemWidth(tabWidth);
    if (ImGui::BeginTabItem("Tab 3"))
    {
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

