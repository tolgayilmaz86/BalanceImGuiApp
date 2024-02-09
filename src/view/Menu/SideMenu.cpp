#include "SideMenu.hpp"
#include "styles/IconsFontAwesome5.h"
#include <string>

namespace VM = View::Menu;

constexpr ImVec4 backgroundColor =
    ImVec4(186.0F / 255.0F, 73.0F / 255.0F, 73.0F / 255.0F, 0.00f);
constexpr ImVec4 backgroundColor2 =
    ImVec4(125.0F / 255.0F, 83.0F / 255.0F, 162.0F / 255.0F, 0.00f);
constexpr ImVec4 backgroundColor3 =
    ImVec4(57.0F / 255.0F, 112.0F / 255.0F, 51.0F / 255.0F, 0.00f);

constexpr static auto window_flags =
    ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
    ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar |
    ImGuiWindowFlags_NoDocking;

VM::SideMenu::SideMenu(std::unique_ptr<WS::IWindow> windowSystem)
    : AbstractMenu(std::move(windowSystem))
{
}

void VM::SideMenu::show()
{
    ImVec2 colStart = ImGui::GetCursorScreenPos();
    {
        ImGui::BeginChild("##SideMenu",
                          ImVec2(60, WS::MENU_WINDOW_HEIGHT),
                          true);

        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10); // round buttons
        std::string tabNames[] = {ICON_FA_CROSSHAIRS,
                                  ICON_FA_EYE,
                                  ICON_FA_COG,
                                  ICON_FA_SAVE};

        for (int i = 0; i < 4; i++)
        {
            std::string it = tabNames[i];
            ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0, 0.5));
            ImGui::PushStyleColor(
                ImGuiCol_Button,
                ImGui::GetStyle().Colors[ImGuiCol_ButtonActive]);
            ImGui::PushStyleColor(ImGuiCol_Text,
                                  ImGui::GetStyle().Colors[ImGuiCol_Text]);
            if (ImGui::Button(it.c_str(), ImVec2(60, 60)))
            {
                //activeTab = i + 1;
            }
            ImGui::Spacing();
            ImGui::PopStyleVar();
            ImGui::PopStyleColor(2);
        }
        ImGui::PopStyleVar();

        ImGui::EndChild();
    }
}

void View::Menu::SideMenu::handleMove(ImVec2 &currentPos)
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
            ImVec2 newWindowPos = ImVec2(currentPos.x + mouseDelta.x,
                                         currentPos.y + mouseDelta.y);

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
